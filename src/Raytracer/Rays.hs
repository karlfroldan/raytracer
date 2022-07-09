module Raytracer.Rays where

import Linear.V4 ( V4 )
import Linear.Vector ((^+^), (^*))

-- | A ray has a vector called the `direction` and a 
-- starting point called the `origin`.
data Ray a =
    Ray { origin    :: V4 a
        , direction :: V4 a
        } deriving (Eq, Show)

-- | Calculates the position of a point given the distance t along the ray.
position :: Num a => Ray a -> a -> V4 a
position r t = origin r ^+^ direction r ^* t