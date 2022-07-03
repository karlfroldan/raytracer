module Test.Raytracer.Transformation where

import Raytracer.Tuple
import Raytracer.Transformation
import Raytracer.FloatEq

import Linear.Matrix ((!*), M44, inv44)
import Linear.V4 (V4 (..))

import Test.Hspec
import GHC.Float (Floating(pi))

import Test.Raytracer.Assertions (shouldApprox)


transTests = do
    describe "transformations.feature" $ do 
        it "Multiplying by a translation matrix" $ do 
            let transform = translation 5 (-3) 2 :: M44 Int
                p         = point (-3) 4 5
            transform !* p `shouldBe` point 2 1 7
    
        it "Multiplying by the inverse of a translation matrix" $ do
            let transform = translation 5 (-3) 2 :: M44 Double
                inv       = inv44 transform
                p         = point (-3) 4 5
                expected  = point (-8) 7 3
            inv !* p =.= expected `shouldBe` True  
        
        it "Translation does not affect vectors" $ do 
            let transform = translation 5 (-3) 2 :: M44 Int 
                v         = vector (-3) 4 5 
            transform !* v `shouldBe` v

        it "A scaling matrix applied to a point" $ do 
            let transform = scaling 2 3 4 :: M44 Int
                p         = point (-4) 6 8
            transform !* p `shouldBe` point (-8) 18 32

        it "A scaling matrix applied to a vector" $ do 
            let transform = scaling 2 3 4 :: M44 Int
                v         = vector (-4) 6 8 
            transform !* v `shouldBe` vector (-8) 18 32
        
        it "Multipying by the inverse of a scaling matrix" $ do 
            let transform = scaling 2 3 4 :: M44 Double
                inv       = inv44 transform 
                v         = vector (-4) 6 8
            inv !* v =.= vector (-2) 2 2 `shouldBe` True
        
        it "Reflection is scaling by a negative value" $ do
            let transform = scaling (-1) 1 1 :: M44 Int 
                p         = point 2 3 4
            transform !* p `shouldBe` point (-2) 3 4
        
        it  "Rotating a point around the x axis (1)" $ do 
            let p         = point 0 1 0 :: V4 Double 
                halfQuarter = rotationX (pi / 4)
                fullQuarter = rotationX (pi / 2)
            halfQuarter !* p =.= point 0 (sqrt 2 / 2) (sqrt 2 / 2) `shouldBe` True
        
        it  "Rotating a point around the x axis (2)" $ do 
            let p         = point 0 1 0 :: V4 Double 
                fullQuarter = rotationX (pi / 2)
            fullQuarter !* p =.= point 0 0 1 `shouldBe` True
        
        it "The inverse of an x-rotation rotates in the opposite direction" $ do 
            let p = point 0 1 0 :: V4 Double 
                halfQuarter = rotationX (pi / 4)
                inv         = inv44 halfQuarter 
            inv !* p =.= point 0 (sqrt 2 / 2) (sqrt 2 / (-2)) `shouldBe` True