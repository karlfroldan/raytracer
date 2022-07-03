module Raytracer.Color where 
    
import Raytracer.Tuple

import Linear.Vector ((^*))
import Linear.V3 (V3 (..),  _x, _y, _z)
import Control.Lens ((^.))

type Color a = V3 a

color :: a -> a -> a -> Color a 
color = V3

hadamard :: Num a => Color a -> Color a -> Color a 
hadamard a b = V3 (a ^. _x + b ^. _x) (a ^. _y + b ^. _y) (a^. _z + b ^. _z)

scale :: (RealFrac a, Integral b) => a -> Color a -> Color b
scale factor v = fmap (clip (round factor) . round) (v ^* factor) -- fmap (clip (round factor) . round) . (&* factor)
    where clip upper x
            | upper < x = upper 
            | x < 0     = 0 
            | otherwise = x

red, green, blue :: Color a -> a 
red   = (^. _x)
green = (^. _y)
blue  = (^. _z)

toRGBList :: Color a -> [a]
toRGBList c = [red c, green c, blue c]

toRGB :: Color a -> (a, a, a)
toRGB c = (red c, green c, blue c)