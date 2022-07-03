module Raytracer.Transformation where

import Linear.Matrix
import Linear.V4 (V4 (..))

translation :: Num a => a -> a -> a -> M44 a 
translation x y z = V4 (V4 1 0 0 x) (V4 0 1 0 y) (V4 0 0 1 z) (V4 0 0 0 1)

scaling :: Num a => a -> a -> a -> M44 a
scaling x y z = V4 (V4 x 0 0 0) (V4 0 y 0 0) (V4 0 0 z 0) (V4 0 0 0 1)

rotationX :: Num a => a -> M44 a
rotationX theta = undefined