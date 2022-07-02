module Raytracer.Color where 
    
import Raytracer.Tuple

type Color a = Tuple3 a

color :: a -> a -> a -> Color a 
color = Tuple3

hadamard :: Num a => Color a -> Color a -> Color a 
hadamard (Tuple3 x y z) (Tuple3 a b c) = 
    Tuple3 (x * a) (y * b) (z * c)

scale :: (RealFrac a, Integral b) => a -> Color a -> Color b
scale factor = fmap (clip (round factor) . round) . (&* factor)
    where clip upper x
            | upper < x = upper 
            | x < 0     = 0 
            | otherwise = x