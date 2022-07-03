module Test.Raytracer.Canvas where 

import Test.Hspec 

import Raytracer.Canvas
import Raytracer.Render
import Raytracer.Color 

renderTests = describe "canvas.feature" $ do 
    it "Constructing the PPM header" $ do 
        let c = newCanvas 5 3 (color 0 0 0) [] :: Canvas (Color Double) 
            ppm = canvasToPpm c 
        ppmHeader (rows c) (cols c) `shouldBe` "P3\n5 3\n255\n"

    it "Constructing the PPM pixel data" $ do 
        let c1 = color 1.5 0 0 :: Color Double 
            c2 = color 0 0.5 0
            c3 = color (-0.5) 0 1
            canvas = newCanvas 5 3 (color 0 0 0) [((0, 0), c1), ((2, 1), c2), ((4, 2), c3)]
            rendered = ppmBody canvas 
        rendered `shouldBe` concat 
               [ "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
               , "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
               , "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"
               ]
