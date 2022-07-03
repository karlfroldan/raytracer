module Main where

import Linear.V4 (V4 (..), _x, _y)
import Linear.Vector ((^+^))

import Control.Lens ((^.))

import Raytracer.Tuple

import Control.Monad (unless, mapM_)
import Raytracer.Canvas
import Raytracer.Color
import Data.Bifunctor
import Raytracer.Render (canvasToPpm)

import System.IO (openFile, IOMode (WriteMode))
import System.Process (callCommand)

data Projectile a = Projectile (V4 a) (V4 a) deriving (Eq, Show)
data Environment a = Environment (V4 a) (V4 a) deriving (Eq, Show)

main :: IO ()
main = do
    let p = Projectile (point 0 1 0) (normalize (vector 1 1 0))    :: Projectile Double
        e = Environment (vector 0 (-0.01) 0) (vector (-0.001) 0 0) :: Environment Double
    canvas <- plot e p
    let filename1 = "output.ppm"
        ppm = canvasToPpm canvas
        filename  = "output.png"
    writeFile filename1 ppm
    callCommand ("convert " ++ filename1 ++ " " ++ filename)
    callCommand ("rm " ++ filename1)

    putStrLn ("Written render to " ++ filename)

plot :: (Show a, RealFrac a, Num a, Ord a) => Environment a -> Projectile a -> IO (Canvas (Color a))
plot env proj = do
    let canvasCols = 301
        canvasRows = 317
        inverted   = (invert . reverseY) (normalizeTuple (tickUntil 0 env proj))
        ticks      = scaleTuple (canvasRows - 1) (canvasCols - 1) <$> inverted 
        red        = color 1 0 0
        black      = color 0 0 0
        path       = (\x -> (x, red)) <$> ticks
        canvas     = newCanvas canvasRows canvasCols black path

    return canvas

-- tickIO :: (Show a, Num a, Ord a) => Environment a -> Projectile a -> IO ()
-- tickIO e p = do
--     let Tuple4 _ yPos  _ _ = getPosition p
--     unless (yPos <= 0) $ do
--         print (getPosition p)
--         let newProj = tick e p
--         tickIO e newProj

tick :: Num a => Environment a -> Projectile a -> Projectile a
tick (Environment gravity wind) (Projectile position velocity) =
    Projectile pos vel
    where
        pos = position ^+^ velocity
        vel = velocity ^+^ gravity ^+^ wind

getPosition :: Projectile a -> V4 a
getPosition (Projectile pos _) = pos

tickUntil :: (Num a, Ord a) => a -> Environment a -> Projectile a -> [(a, a)]
tickUntil limit env proj
    | yPos <= 0 = []
    | otherwise = (xPos, yPos) : tickUntil limit env (tick env proj)
    where
        pos = getPosition proj
        xPos = pos ^. _x 
        yPos = pos ^. _y

-- | min-max feature scaling normalization. 
-- We want to bring everything to the interval [0, 1]
normalizeList :: (Ord a, RealFrac a) => [a] -> [a]
normalizeList xs = (\x -> (x - minXs) / (maxXs - minXs)) <$> xs
    where minXs = minimum xs
          maxXs = maximum xs

normalizeTuple :: (Ord a, RealFrac a) => [(a, a)] -> [(a, a)]
normalizeTuple = uncurry zip . bimap normalizeList normalizeList . unzip


-- We want to scale it on the bounds of our canvas
scaleTuple :: (RealFrac a) => Int -> Int -> (a, a) -> (Int, Int)
scaleTuple w h (x, y) = (round $ fromIntegral w * x, round $ fromIntegral h * y)

-- Unfortunately, our PPM code writes it with x-y inverted. So we want to invert the axes.
invert :: [(b, a)] -> [(a, b)]
invert = fmap invert'
    where invert' (x, y) = (y, x)

-- The y-coordinate is upside down so we reverse it.
reverseY :: RealFrac a => [(a, a)] -> [(a, a)]
reverseY = fmap (second (1 -))