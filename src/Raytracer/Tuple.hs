module Raytracer.Tuple where

import Raytracer.FloatEq

data Tuple4 a = Tuple4 a a a a deriving (Eq)
data Tuple3 a = Tuple3 a a a deriving (Eq)

instance Show a => Show (Tuple4 a) where 
    show (Tuple4 x y z w) =
        concat [ "(", show x, ", ", show y 
               , ", ", show z, ", ", show w, ")"]

instance Show a => Show (Tuple3 a) where 
    show (Tuple3 x y z) =
        concat [ "(", show x, ", ", show y 
               , ", ", show z, ")"]

instance Functor Tuple4 where
    fmap f (Tuple4 x y z w) = Tuple4 (f x) (f y) (f z) (f w)

instance Semigroup a => Semigroup (Tuple4 a) where
    Tuple4 x1 x2 x3 x4 <> Tuple4 y1 y2 y3 y4 =
        Tuple4 (x1 <> y1) (x2 <> y2) (x3 <> y3) (x4 <> y4)

instance Foldable Tuple4 where
    foldr f a (Tuple4 x y z w) = foldr f a [x, y, z, w]

instance FloatEq a => FloatEq (Tuple4 a) where
    Tuple4 x1 x2 x3 x4 =.= Tuple4 y1 y2 y3 y4 =
        (x1 =.= y1) && (x2 =.= y2) && (x3 =.= y3) && (x4 =.= y4)

instance Functor Tuple3 where
    fmap f (Tuple3 x y z) = Tuple3 (f x) (f y) (f z)

instance Foldable Tuple3 where
    foldr f a (Tuple3 x y z) = foldr f a [x, y, z]

instance Semigroup a => Semigroup (Tuple3 a) where
    Tuple3 x1 x2 x3 <> Tuple3 y1 y2 y3 =
        Tuple3 (x1 <> y1) (x2 <> y2) (x3 <> y3)

instance FloatEq a => FloatEq (Tuple3 a) where
    Tuple3 x1 x2 x3 =.= Tuple3 y1 y2 y3 =
        (x1 =.= y1) && (x2 =.= y2) && (x3 =.= y3)


point :: Num a => a -> a -> a -> Tuple4 a
point x y z = Tuple4 x y z 1

vector :: Num a => a -> a -> a -> Tuple4 a
vector x y z = Tuple4 x y z 0

class Tuple a where
    (<+>) :: a -> a -> a
    (<->) :: a -> a -> a
    neg   :: a -> a
    (&*&) :: a -> a -> a


infixl 6 <+>
infixl 6 <->
infixl 7 &*
infixl 7 &/
infixl 7 &*&

instance Num a=> Tuple (Tuple4 a) where
    Tuple4 x1 x2 x3 x4 <+> Tuple4 y1 y2 y3 y4 =
        Tuple4 (x1 + y1) (x2 + y2) (x3 + y3) (x4 + y4)

    Tuple4 x1 x2 x3 x4 <-> Tuple4 y1 y2 y3 y4 =
        Tuple4 (x1 - y1) (x2 - y2) (x3 - y3) (x4 - y4)

    neg (Tuple4 x y z w) =
        Tuple4 (negate x) (negate y) (negate z) (negate w)
    
    Tuple4 x1 x2 x3 x4 &*& Tuple4 y1 y2 y3 y4 = 
        Tuple4 (x1 * y1) (x2 * y2) (x3 * y3) (x4 * y4)

instance Num a => Tuple (Tuple3 a) where
    Tuple3 x1 x2 x3 <+> Tuple3 y1 y2 y3 =
        Tuple3 (x1 + y1) (x2 + y2) (x3 + y3)

    Tuple3 x1 x2 x3 <-> Tuple3 y1 y2 y3 =
        Tuple3 (x1 - y1) (x2 - y2) (x3 - y3)

    neg (Tuple3 x y z) =
        Tuple3 (negate x) (negate y) (negate z)

    Tuple3 x1 x2 x3 &*& Tuple3 y1 y2 y3 = 
        Tuple3 (x1 * y1) (x2 * y2) (x3 * y3)

(&*) :: (Functor t, Num a) => t a -> a -> t a
t &* c = fmap (*c) t

(&/)  :: (Functor t, Floating a) => t a -> a -> t a
t &/ c = fmap (/ c) t

magnitude :: (Foldable t, Functor t, Floating a) => t a -> a
magnitude t = sqrt (sum ((^2) <$> t))

normalize :: (Foldable t, Functor t, Floating a) => t a -> t a 
normalize v = (/ magnitude v) <$> v

dot :: (Foldable t, Tuple (t a), Num a) => t a -> t a -> a 
dot x y = sum (x &*& y)

cross4 :: Num a => Tuple4 a -> Tuple4 a -> Tuple4 a
cross4 (Tuple4 x1 y1 z1 w1) (Tuple4 x2 y2 z2 w2) = 
    Tuple4 (y1 * z2 - z1 * y2) (z1 * x2 - x1 * z2) (x1 * y2 - y1 * x2) 0