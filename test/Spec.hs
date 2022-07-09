import Test.Hspec

import Test.Raytracer.Transformation
import Test.Raytracer.Rays

main :: IO ()
main = hspec $ do
    transTests
    raysTests