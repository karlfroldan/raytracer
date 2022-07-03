module Test.Raytracer.Matrix where 

import Test.Hspec

import Raytracer.Matrix
import Raytracer.Tuple

matrixTests = describe "matrices.feature" $ do 
    it "Multiplying two matrices" $ do 
        let a = fromListM [[1, 2, 3, 4], [5, 6, 7, 8], [9, 8, 7, 6], [5, 4, 3, 2]]
            b = fromListM [[-2, 1, 2, 3], [3, 2, 1, -1], [4, 3, 6, 5], [1, 2, 7, 8]]
            e = fromListM [[20, 22, 50, 48], [44, 54, 114, 108], [40, 58, 110, 102], [16, 26, 46, 42]]
        a !*! b `shouldBe` e

    it "A matrix multiplied by a tuple" $  do 
        let a = fromListM [[1, 2, 3, 4], [2, 4, 4, 2], [8, 6, 4, 1], [0, 0, 0, 1]]
            b = Tuple4 1 2 3 1
            e = Tuple4 18 24 33 1 
        a !*> b `shouldBe` e
    
    it "Multiplying a matrix by the identity matrix" $ do 
        let a = fromListM [[0, 1, 2, 4], [1, 2, 4, 8], [2, 4, 8, 16], [2, 4, 16, 32]]
            i = idMat 4 
        a !*! i `shouldBe` a

    it "Multiplying the identity matrix by a tuple" $ do 
        let a = Tuple4 1 2 3 4 
            i = idMat 4 
        i !*> a `shouldBe` a
    
    it "Transposing a matrix" $ do 
        let a = fromListM [[0, 9, 3, 0], [9, 8, 0, 8], [1, 8, 5, 3], [0, 0, 5, 8]]
            b = fromListM [[0, 9, 1, 0], [9, 8, 8, 0], [3, 0, 5, 5], [0, 8, 3, 8]]
        transpose a `shouldBe` b

    it "Transposing the identity matrix" $ do 
        let i = idMat 5 :: Matrix Int
        transpose i `shouldBe` i