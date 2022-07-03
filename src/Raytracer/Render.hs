module Raytracer.Render where

import Raytracer.Canvas
import Raytracer.Color
import Data.Foldable (Foldable(foldl'))
import Data.List (intersperse, transpose)

import Data.List.Split (chunksOf)

canvasToPpm :: RealFrac a => Canvas (Color a) -> String
canvasToPpm c = ppmHeader (cols c) (rows c) ++ ppmBody c

-- | Create a list per color channel.
colorsToList :: [Color a] -> ([a], [a], [a])
colorsToList =
    foldr (\c (rs, gs, bs)  ->
        (red c:rs, green c:gs, blue c:bs))
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
    where colors = concat $ toRGBList <$> canvasToList c
          chunked = unwords . fmap show <$> chunksOf 17 colors

          