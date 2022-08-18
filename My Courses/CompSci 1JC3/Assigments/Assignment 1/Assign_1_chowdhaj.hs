-- MacID: Chowdhaj
-- Date: September 29th, 2017
-- Assignment 1: Cubic Root Finder

cubicQ :: Float -> Float -> Float -> Float
cubicQ a b c = (3 * a * c - b^2) / (9 * a^2)

cubicR :: Float -> Float -> Float -> Float -> Float
cubicR a b c d = ((9 * a * b * c) - (27 * a^2 * d) - (2 * b^3)) / (54 * a^3)

cubicS :: Float -> Float -> Float
cubicS q r = cubeRoot(r + sqrt(q^3 + r^2))

cubicT :: Float -> Float -> Float
cubicT q r = cubeRoot(r - sqrt(q^3 + r^2))

cubeRoot :: Float -> Float
cubeRoot x = if x >= 0 then x ** (1/3) else (abs x) ** (1/3) * (-1)

cubicRealSolution :: Float -> Float -> Float -> Float -> Float
cubicRealSolution a b c d = let
        q = cubicQ a b c
        r = cubicR a b c d
        z = b / (3 * a)
    in (cubicS q r) + (cubicT q r) - z