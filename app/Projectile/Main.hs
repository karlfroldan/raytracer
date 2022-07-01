module Main where 
import Raytracer.Tuple

import Control.Monad (unless)



data Projectile a = Projectile (Tuple4 a) (Tuple4 a) deriving (Eq, Show)
data Environment a = Environment (Tuple4 a) (Tuple4 a) deriving (Eq, Show)

main :: IO ()
main = do 
    let p = Projectile (point 0 1 0) (normalize (vector 1 1 0)) :: Projectile Double
        e = Environment (vector 0 (-0.1) 0) (vector (-0.01) 0 0) :: Environment Double 
    keepTicking e p

keepTicking :: (Show a, Num a, Ord a) => Environment a -> Projectile a -> IO ()
keepTicking e p = do 
    let Tuple4 _ yPos  _ _ = getPosition p
    unless (yPos <= 0) $ do 
        putStrLn $ show $ getPosition p
        let newProj = tick e p 
        keepTicking e newProj

tick :: Num a => Environment a -> Projectile a -> Projectile a 
tick (Environment gravity wind) (Projectile position velocity) = 
    Projectile pos vel 
    where 
        pos = position <+> velocity
        vel = velocity <+> gravity <+> wind

getPosition :: Projectile a -> Tuple4 a 
getPosition (Projectile pos _) = pos