module Raytracer.Canvas where

import Data.Array

import Data.List (sortBy)

import Raytracer.Color ( Color, scale )

data Canvas a = Canvas
    { rows   :: Int
    , cols  :: Int
    , display :: Array (Int, Int) a
    } deriving (Eq, Show)

newCanvas :: Int -> Int -> a -> [((Int, Int), a)] -> Canvas a
newCanvas rows cols init pixels = Canvas rows cols arrayC
    where arrayC = listArray ((0, 0), (rows - 1, cols - 1)) (repeat init) // pixels

canvasToList :: (RealFrac a, Integral b) => Canvas (Color a) -> [Color b]
canvasToList c = scale 255 . snd <$> assocs (display c)