module Raytracer.Render where

import Raytracer.Canvas
import Raytracer.Color
import Data.Foldable (Foldable(foldl'))
import Raytracer.Tuple (Tuple3 (..))
import Data.List (intersperse)

import Data.List.Split (chunksOf)

canvasToPpm :: RealFrac a => Canvas (Color a) -> String
canvasToPpm c = ppmHeader (width c) (height c) ++ ppmBody c

-- | Create a list per color channel.
colorsToList :: [Color a] -> ([a], [a], [a])
colorsToList =
    foldr (\(Tuple3 r g b) (rs, gs, bs)  ->
        (r:rs, g:gs, b:bs))
        ([], [], [])

-- | From each color channel list, create a single-spaced row .
showLine ::Show a => [a] -> [Char]
showLine =  unwords . map show

-- | Initial Color
initColor :: Color Double
initColor = color 0 0 0

ppmHeader :: Int -> Int -> String
ppmHeader w h =
    concat [ "P3\n", show w, " ", show h, "\n255\n"]

ppmBody :: RealFrac a => Canvas (Color a) -> String
ppmBody c = unlines chunked ++ "\n"
    where colors = concat $ (\(Tuple3 r g b) -> [r, g, b]) <$> canvasToList c
          chunked = unwords . fmap show <$> chunksOf 17 colors

          