module Raytracer.Render where 

import Raytracer.Canvas
import Raytracer.Color

canvasToPpm :: Canvas a -> String 
canvasToPpm c =
    concat [ "P3\n", show (width c), " ", show (height c), "\n255\n"]

initColor :: Color Double
initColor = color 0 0 0

