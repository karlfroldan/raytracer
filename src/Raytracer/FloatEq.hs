module Raytracer.FloatEq where

class FloatEq a where
    (=.=) :: a -> a -> Bool

infix 4 =.=

instance FloatEq Float where 
    x =.= y = abs (x - y) < eps 
        where eps = 0.00001

instance FloatEq Double where 
    x =.= y = abs (x - y) < eps 
        where eps = 0.00001