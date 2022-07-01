module Canvas where 

import Test.Hspec 

import Raytracer.Canvas
import Raytracer.Render

renderTests = describe "canvas.feature" $ do 
    it "Constructing the PPM header" $ do 
        let c = newCanvas 5 3 0 :: Canvas Int 
            ppm = canvasToPpm c 
        ppm `shouldBe` "P3\n5 3\n255\n"