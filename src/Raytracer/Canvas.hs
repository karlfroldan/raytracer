module Raytracer.Canvas where

import Data.Array

import Data.List (sortBy)

import Raytracer.Color
import Raytracer.Tuple ((&*))

data Canvas a = Canvas
    { width   :: Int
    , height  :: Int
    , display :: Array (Int, Int) a
    } deriving (Eq, Show)

newCanvas :: Int -> Int -> a -> [((Int, Int), a)] -> Canvas a
newCanvas w h init pixels = Canvas w h arrayC
    where arrayC = listArray ((0, 0), (w - 1, h - 1)) (repeat init) // pixels

canvasToList :: (RealFrac a, Integral b) => Canvas (Color a) -> [Color b]
canvasToList c = scale 255 . snd <$> assocs (display c)