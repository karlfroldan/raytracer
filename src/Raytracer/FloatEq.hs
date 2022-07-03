module Raytracer.FloatEq where

import Linear.V1 
import Linear.V2 
import Linear.V3 
import Linear.V4
import Data.Functor.Classes (Eq1(liftEq))

class FloatEq a where
    (=.=) :: a -> a -> Bool

infix 4 =.=

instance FloatEq Float where 
    x =.= y = abs (x - y) < eps 
        where eps = 0.00001

instance FloatEq Double where 
    x =.= y = abs (x - y) < eps 
        where eps = 0.00001

instance FloatEq a => FloatEq (V1 a) where 
    (=.=) = liftEq (=.=)

instance FloatEq a => FloatEq (V2 a) where 
    (=.=) = liftEq (=.=)

instance FloatEq a => FloatEq (V3 a) where 
    (=.=) = liftEq (=.=)

instance FloatEq a => FloatEq (V4 a) where 
    (=.=) = liftEq (=.=)