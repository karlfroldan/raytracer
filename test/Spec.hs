import Test.Hspec
import Tuple
import Canvas

main :: IO ()
main = hspec $ do
    tupleTests
    --renderTests