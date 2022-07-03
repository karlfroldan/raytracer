module Raytracer.Matrix where

import Raytracer.Tuple
-- import Data.List (transpose)
import qualified Data.List as L

import Raytracer.FloatEq

-- | A matrix in row major order.
newtype Matrix a = Matrix [[a]] deriving Eq

instance Functor Matrix where
    fmap f (Matrix lst) = Matrix $ fmap (fmap f) lst

instance Show a => Show (Matrix a) where
    show (Matrix mat) = unlines formatted
        where formatted  = fmap (unwords . fmap show) mat

fromListM :: [[a]] -> Matrix a
fromListM = Matrix

transpose :: Matrix a -> Matrix a
transpose (Matrix mat) = Matrix (L.transpose mat)

instance FloatEq a => FloatEq (Matrix a) where
    Matrix m =.= Matrix n = and (fmap (uncurry (=.=)) concatted)
        where concatted = zip (concat m) (concat n)

-- https://samprocter.com/2012/11/matrix-multiplication-in-haskell/
mmult :: Num a => [[a]] -> [[a]] -> [[a]]
mmult a b = [[sum $ zipWith (*) ar bc | bc <- L.transpose b] | ar <- a]

-- | Matrix-Matrix multiplication
(!*!) :: Num a => Matrix a -> Matrix a -> Matrix a
Matrix m !*! Matrix n = Matrix (mmult m n)

-- | Matrix-tuple multiplication, assuming Tuple4
(!*>) :: Num a => Matrix a -> Tuple4 a -> Tuple4 a
m !*> t = matColToTuple4 (m !*! tuple4ToMatrix t)

tuple4ToMatrix :: Tuple4 a -> Matrix a 
tuple4ToMatrix (Tuple4 a b c d) = Matrix [[a], [b], [c], [d]]

matRowToTuple4 :: Matrix a -> Tuple4 a 
matRowToTuple4 (Matrix xs) = Tuple4 a b c d 
    where  a:b:c:d:_ = head xs

matColToTuple4 :: Matrix a -> Tuple4 a 
matColToTuple4 (Matrix xs) = Tuple4 a b c d 
    where a:b:c:d:_ = head <$> xs

-- https://gist.github.com/CMCDragonkai/ba838156d7354d8e32cd
idMat :: Num a => Int -> Matrix a 
idMat n = Matrix [[fromIntegral $ fromEnum $ x == y | y <- [1..n]] | x <- [1..n]]