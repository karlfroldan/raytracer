module Test.Raytracer.Transformation where

import Raytracer.Tuple
import Raytracer.Transformation
import Raytracer.FloatEq

import Linear.Matrix ((!*), (!*!), M44, inv44)
import Linear.V4 (V4 (..))

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
            inv !* p `shouldSatisfy` (=.= expected)  
        
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
            inv !* v `shouldSatisfy` (=.= vector (-2) 2 2)
        
        it "Reflection is scaling by a negative value" $ do
            let transform = scaling (-1) 1 1 :: M44 Int 
                p         = point 2 3 4
            transform !* p `shouldBe` point (-2) 3 4
        
        it  "Rotating a point around the x axis (1)" $ do 
            let p         = point 0 1 0 :: V4 Double 
                halfQuarter = rotationX (pi / 4)
                fullQuarter = rotationX (pi / 2)
            halfQuarter !* p `shouldSatisfy` (=.= point 0 (sqrt 2 / 2) (sqrt 2 / 2))
        
        it  "Rotating a point around the x axis (2)" $ do 
            let p         = point 0 1 0 :: V4 Double 
                fullQuarter = rotationX (pi / 2)
            fullQuarter !* p `shouldSatisfy` (=.= point 0 0 1)
        
        it "The inverse of an x-rotation rotates in the opposite direction" $ do 
            let p = point 0 1 0 :: V4 Double 
                halfQuarter = rotationX (pi / 4)
                inv         = inv44 halfQuarter 
            inv !* p `shouldSatisfy` (=.= point 0 (sqrt 2 / 2) (sqrt 2 / (-2))) 
        
        it "Rotation a point around the y axis (1)" $ do 
            let p = point 0 0 1 :: V4 Double 
                halfQuarter = rotationY (pi / 4)
            halfQuarter !* p `shouldSatisfy` (=.= point (sqrt 2 / 2) 0 (sqrt 2 / 2))
        
        it "Rotation a point around the y axis (2)" $ do 
            let p = point 0 0 1 :: V4 Double 
                halfQuarter = rotationY (pi / 2)
            halfQuarter !* p `shouldSatisfy` (=.= point 1 0 0)
        
        it "Rotation a point around the z axis (1)" $ do 
            let p = point 0 1 0 :: V4 Double 
                halfQuarter = rotationZ (pi / 4)
            halfQuarter !* p `shouldSatisfy` (=.= point (-sqrt 2 / 2) (sqrt 2 / 2) 0)
        
        it "Rotation a point around the z axis (2)" $ do 
            let p = point 0 1 0 :: V4 Double 
                halfQuarter = rotationZ (pi / 2)
            halfQuarter !* p `shouldSatisfy` (=.= point (-1) 0 0)

        it "A shearing transformation moves x in proportion to y" $ do 
            let t = shearing 1 0 0 0 0 0 :: M44 Double 
                p = point 2 3 4
            t !* p `shouldSatisfy` (=.= point 5 3 4)
        
        it "A shearing transformation moves x in proportion to z" $ do 
            let t = shearing 0 1 0 0 0 0 :: M44 Double 
                p = point 2 3 4
            t !* p `shouldSatisfy` (=.= point 6 3 4)
        
        it "A shearing transformation moves y in proportion to x" $ do 
            let t = shearing 0 0 1 0 0 0 :: M44 Double 
                p = point 2 3 4
            t !* p `shouldSatisfy` (=.= point 2 5 4)
        
        it "A shearig transformation moves y in proportion to z" $ do 
            let t = shearing 0 0 0 1 0 0 :: M44 Double 
                p = point 2 3 4 
            t !* p `shouldSatisfy` (=.= point 2 7 4)
        
        it "A shearing transformation moves z in proportion to x" $ do 
            let t = shearing 0 0 0 0 1 0 :: M44 Double 
                p = point 2 3 4
            t !* p `shouldSatisfy` (=.= point 2 3 6)
        
        it "A shearing transformation moves z in propoertion to y" $ do 
            let t = shearing 0 0 0 0 0 1 :: M44 Double 
                p = point 2 3 4
            t !* p `shouldSatisfy` (=.= point 2 3 7)
        
        it "Individual transformations are applied in sequence - rotation" $ do 
            let p = point 1 0 1 :: V4 Double 
                a = rotationX (pi / 2)
                b = scaling 5 5 5
                c = translation 10 5 7
            a !* p `shouldSatisfy` (=.= point 1 (-1) 0)
        it "Individual transformations are applied in sequence - scaling" $ do 
            let p = point 1 0 1 :: V4 Double 
                a = rotationX (pi / 2)
                b = scaling 5 5 5
                c = translation 10 5 7
                p2 = a !* p
            b !* p2 `shouldSatisfy` (=.= point 5 (-5) 0)
        it "Individual transformations are applied in sequence - translation" $ do 
            let p = point 1 0 1 :: V4 Double 
                a = rotationX (pi / 2)
                b = scaling 5 5 5
                c = translation 10 5 7
                p2 = a !* p 
                p3 = b !* p2 
            c !* p3 `shouldSatisfy` (=.= point 15 0 7)
        
        it "Chained transformations must be applied in reverse order" $ do 
            let p = point 1 0 1 :: V4 Double 
                a = rotationX (pi / 2)
                b = scaling 5 5 5
                c = translation 10 5 7
            a |> b |> c !* p `shouldSatisfy` (=.= point 15 0 7)