module Tuple where 

import Test.Hspec

import Raytracer.Tuple
import Raytracer.FloatEq
import Raytracer.Color

tupleTests = describe "tuples.feature" $ do
    it "Adding to tuples" $ do 
        point 3 (-2) 5 <+> vector (-2) 3 1 `shouldBe` point 1 1 6
    
    it "Subtracting two points" $ do 
        point 3 2 1 <-> point 5 6 7 `shouldBe` vector (-2) (-4) (-6)
    
    it "Subtracting a vector from a point" $ do 
        point 3 2 1 <-> vector 5 6 7 `shouldBe` point (-2) (-4) (-6)

    it "Subtracting two vectors" $ do 
        vector 3 2 1 <-> vector 5 6 7 `shouldBe` vector (-2) (-4) (-6)
    
    it "Multiplying a tuple by a scalar" $ do 
        let a = Tuple4 1 (-2) 3 (-4) :: Tuple4 Double
        a &* 3.5 =.= Tuple4 3.5 (-7) 10.5 (-14) `shouldBe` True

    it "Multiplying a tuple by a fraction" $ do 
        let a = Tuple4 1 (-2) 3 (-4) :: Tuple4 Double
        a &* 0.5 =.= Tuple4 0.5 (-1) 1.5 (-2) `shouldBe` True
    
    it "Dividing a tuple by a scalar" $ do 
        let a = Tuple4 1 (-2) 3 (-4) :: Tuple4 Double
        a &/ 2 =.= Tuple4 0.5 (-1) 1.5 (-2) `shouldBe` True
    
    it "Computing the magnitude of vector(1, 0, 0)" $ do 
        let v = vector 1 0 0 :: Tuple4 Double 
        magnitude v =.= 1 `shouldBe` True
    
    it "Computing the magnitude of vector(0, 1, 0)" $ do 
        let v = vector 0 1 0 :: Tuple4 Double 
        magnitude v =.= 1 `shouldBe` True

    it "Computing the magnitude of vector(0, 0, 1)" $ do 
        let v = vector 0 0 1 :: Tuple4 Double 
        magnitude v =.= 1 `shouldBe` True

    it "Computing the magnitude of vector(1, 2, 3)" $ do 
        let v = vector 1 2 3 :: Tuple4 Double 
        magnitude v =.= sqrt 14 `shouldBe` True

    it "Computing the magnitude of vector(-1, -2, -3)" $ do 
        let v = vector (-1) (-2) (-3) :: Tuple4 Double 
        magnitude v =.= sqrt 14 `shouldBe` True

    it "Normalizing vector (4, 0, 0) gives (1, 0, 0)" $ do 
        let v = vector 4 0 0 :: Tuple4 Double
        normalize v =.= vector 1 0 0 `shouldBe` True

    it "Normalizing vector (1, 2, 3)" $ do 
        let v = vector 1 2 3 :: Tuple4 Double 
        normalize v =.= vector (1/sqrt 14) (2/sqrt 14) (3 /sqrt 14) `shouldBe` True

    it "The magnitude of a normalized vector" $ do 
        let v = vector 1 2 3 :: Tuple4 Double
            norm = normalize v 
        magnitude norm =.= 1 `shouldBe` True
    
    it "The dot product of two tuples" $ do 
        let a = vector 1 2 3 :: Tuple4 Double 
            b = vector 2 3 4 :: Tuple4 Double 
        dot a b =.= 20 `shouldBe` True
    
    it "The cross product of two vectors (1)" $ do 
        let a = vector 1 2 3 :: Tuple4 Double 
            b = vector 2 3 4 :: Tuple4 Double 
        
        cross4 a b =.= vector (-1) 2 (-1) `shouldBe` True

    it "The cross product of two vectors (2)" $ do 
        let a = vector 1 2 3 :: Tuple4 Double 
            b = vector 2 3 4 :: Tuple4 Double 
        
        cross4 b a =.= vector 1 (-2) 1 `shouldBe` True
    
    it "Adding colors" $ do 
        let c1 = color 0.9 0.6 0.75 :: Color Double 
            c2 = color 0.7 0.1 0.25 
        c1 <+> c2 =.= color 1.6 0.7 1.0 `shouldBe` True
    
    it "Subtracting colors" $ do 
        let c1 = color 0.9 0.6 0.75 :: Color Double 
            c2 = color 0.7 0.1 0.25 
        c1 <-> c2 =.= color 0.2 0.5 0.5 `shouldBe` True

    it "Multiplying a color by a scalar" $ do 
        let c = color 0.2 0.3 0.4 :: Color Double
        c &* 2 =.= color 0.4 0.6 0.8 `shouldBe` True

    it "Multiplying colors" $ do 
        let c1 = color 1 0.2 0.4 :: Color Double 
            c2 = color 0.9 1 0.1
        hadamard c1 c2 =.= color 0.9 0.2 0.04 `shouldBe` True