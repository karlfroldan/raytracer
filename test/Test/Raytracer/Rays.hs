module Test.Raytracer.Rays where 

import Test.Hspec

import Raytracer.Tuple
import Raytracer.Rays
import Raytracer.FloatEq

import Linear.V4 (V4 (..))

raysTests = do 
    describe "rays.feature" $  do 
        it "Creating and querying a ray" $ do 
            let origin' = point 1 2 3 :: V4 Int 
                dir'    = vector 4 5 6
                r       = Ray origin' dir'
            -- then 
            origin r `shouldBe` origin'
            direction r `shouldBe` dir'

        it "Computing a point from a distance" $ do 
            let r = Ray (point 2 3 4) (vector 1 0 0) :: Ray Double 
            position r 0 `shouldSatisfy` (=.= point 2 3 4)
            position r 1 `shouldSatisfy` (=.= point 3 3 4)
            position r (-1) `shouldSatisfy` (=.= point 1 3 4)
            position r 2.5 `shouldSatisfy` (=.= point 4.5 3 4)