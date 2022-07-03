module Test.Raytracer.Assertions where 

import Raytracer.FloatEq
import Control.Monad (unless)
import Test.HUnit (assertFailure, Assertion)
import Test.Hspec (Expectation)

shouldApprox :: (FloatEq a, Show a) => a -> a -> Expectation
actual `shouldApprox` expected =
    unless (actual =.= expected) (assertFailure msg)
        where msg = "approximation error\nexpected: " ++ show expected ++
                    "\n but got: " ++ show actual