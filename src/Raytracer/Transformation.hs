module Raytracer.Transformation where

import Linear.Matrix
import Linear.V4 (V4 (..))
import Linear (Additive)

translation :: Num a => a -> a -> a -> M44 a 
translation x y z = V4 (V4 1 0 0 x) (V4 0 1 0 y) (V4 0 0 1 z) (V4 0 0 0 1)

scaling :: Num a => a -> a -> a -> M44 a
scaling x y z = V4 (V4 x 0 0 0) (V4 0 y 0 0) (V4 0 0 z 0) (V4 0 0 0 1)

rotationX, rotationY, rotationZ :: Floating a => a -> M44 a
rotationX theta = V4 (V4 1 0 0 0) (V4 0 cosT (-sinT) 0) (V4 0 sinT cosT 0) (V4 0 0 0 1)
    where cosT = cos theta 
          sinT = sin theta
    
rotationY theta = V4 (V4 cosT 0 sinT 0) (V4 0 1 0 0) (V4 (-sinT) 0 cosT 0) (V4 0 0 0 1) 
    where cosT = cos theta 
          sinT = sin theta

rotationZ theta = V4 (V4 cosT (-sinT) 0 0) (V4 sinT cosT 0 0) (V4 0 0 1 0) (V4 0 0 0 1)
    where cosT = cos theta 
          sinT = sin theta

shearing :: Num a => a -> a -> a -> a -> a -> a -> M44 a
shearing x_y x_z y_x y_z z_x z_y =
    V4 (V4 1     x_y   x_z   0) 
       (V4 y_x   1     y_z   0) 
       (V4 z_x   z_y   1     0)
       (V4 0     0     0     1)

infixl 7 |>

-- | Reverse of matrix multiplication. I will use this for chaining
-- matrix transformations.
(|>) :: (Functor m, Foldable t, Additive t, Additive n, Num a)
    => t (n a) -> m (t a) -> m (n a)
(|>) = flip (!*!)