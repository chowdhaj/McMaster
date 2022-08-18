module VectorSpace where

type Vector = (Double, Double, Double)

vecZero :: Double
vecZero (a,b,c) = if a == b && b == c then 0 else 1

vecScalarProd :: Double -> Vector -> Vector

vecSum :: Vector -> Vector -> Vector

vecMagnitude :: Vector -> Double

vecF :: Vector -> [Vector] -> [Double]
vecF x y = 

{-

Function: Name of the function being tested.
Test Case Number: The number of the test case. 
Input: Inputs for function.
Expected Output: Expected output for the function. 
Actual Output: Actual output for the function.

-}