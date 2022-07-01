module Raytracer.Canvas where

import Data.Array

data Canvas a = Canvas
    { width   :: Int
    , height  :: Int
    , display :: Array (Int, Int) a
    } deriving (Eq, Show)

newCanvas :: Int -> Int -> a -> Canvas a
newCanvas w h init = Canvas w h arrayC
    where arrayC = listArray ((0, 0), (w - 1, h - 1)) (repeat init)

{-
We want a function that takes a list
[(Ix, Element)] and then basically fills everything else with `init`.
-}
drawCanvas :: Int -> Int -> a -> [((Int, Int), a)] -> Canvas a 
drawCanvas w h init elems = undefined