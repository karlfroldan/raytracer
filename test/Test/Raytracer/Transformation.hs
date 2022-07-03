module Test.Raytracer.Transformation where

import Raytracer.Transformation
import Raytracer.Tuple
import Raytracer.FloatEq

import Linear.Matrix ((!*), M44, inv44)

import Test.Hspec
import GHC.Float (Floating(pi))

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
        
        it  "Rotating a point around the x axis" $ do 
            let p         = point 0 1 0 :: M44 Double 
                halfQuarter = rotationX (pi / 4)
                fullQuarter = rotationX (pi / 2)
            return ()