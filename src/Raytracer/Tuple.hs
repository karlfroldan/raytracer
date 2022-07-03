module Raytracer.Tuple where

import Raytracer.FloatEq

import Linear.V4 
import Linear.V3


point :: Num a => a -> a -> a -> V4 a
point x y z = V4 x y z 1

vector :: Num a => a -> a -> a -> V4 a
vector x y z = V4 x y z 0

magnitude :: (Foldable t, Functor t, Floating a) => t a -> a
magnitude t = sqrt (sum ((^2) <$> t))

normalize :: (Foldable t, Functor t, Floating a) => t a -> t a 
normalize v = (/ magnitude v) <$> v
