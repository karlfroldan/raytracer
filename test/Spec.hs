import Test.Hspec
import Test.Raytracer.Tuple
import Test.Raytracer.Canvas
import Test.Raytracer.Matrix

main :: IO ()
main = hspec $ do
    tupleTests
    --renderTests
    matrixTests