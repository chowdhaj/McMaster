-- Name  : Jatin Chowdhary
-- Date  : November 31st, 2017
-- MacID : Chowdhaj

module DefiniteIntegral where
import Test.QuickCheck

{-
This function computes an approximation to a definite integral using the trapezoidal rule where
'a' is the first value, 'b' is the second value, 'n' is the number of partitions/steps 
and g represents the function using lambdas/anonymous classes. First it calculates deltaX, and then
uses this information to compute the area under the curve. The function 'calculateArea' uses deltaX,
along with the other arguments, 'a', 'b', and 'g' to compute the area under the curve. 
-}
definiteIntegral :: Double -> Double -> (Double -> Double) -> Integer -> Double 
definiteIntegral _ _ _ 0 = 0.0 -- If 'n' == 0, I'll return 0. Though I can return an error --> error "Not A Valid Input; Please Try Again"
definiteIntegral 0 0 _ _ = 0.0 -- If both 'a' and 'b' are 0, then return 0.0 because there is no area to approximate
definiteIntegral a b g n = let
    deltaX = (b - a) / fromIntegral n -- Computes deltaX as defined in the trapezoidal rule
    f      = calculateArea a b g deltaX
  in f * deltaX / 2

{-
This function calculates the area of the trapezoids from f(a) to f(b), where firstX is f(a),
lastX is f(b), and everything in between is calculated by the function 'mapMiddle' because these
terms share one thing in common, they are all multiplied by two. Hence, it would be effective to
use list comphrehensions to compute this. Finally, firstX, lastX, and middleX are all summed up.
-}
calculateArea :: (Enum a, Num a, Num b) => a -> a -> (a -> b) -> a -> b
calculateArea a b g z = let
    firstX  = g a -- Computes the first term, f(a)
    lastX   = g b -- Computes the last term, f(b)
    middleX = mapMiddle (a+z) (b-z) g z -- This calculates all the terms between f(a) and f(b)
  in firstX + lastX + middleX -- Sums up f(a) to f(b)

{-
This function is akin to a helper function. It assists the function 'calculateArea' in computing all
terms between f(a) and f(b). These terms are all multiplied by two. Furthermore, 'z' must be added to 
f(a) to compute the term after it, and this carries on until it reaches f(b). The step for the list
[a..b] is 'z' as represented by [a,(a+z)..b]. Recursion can be used to define this, but list 
comphrehension is easier to read, code and understand. See obsolete code below.
-}
mapMiddle :: (Num a, Num b, Enum b) => b -> b -> (b -> a) -> b -> a
mapMiddle a b g z = sum $ [2 * (g x)| x <- [a,(a+z)..b]]

{-
This function calculates the area of a circle by integrating over the area that is ONLY in quadrant
one (the positive quadrant). Then, this area is multiplied by 4 to find the totalArea of the circle.
Note, this is an approximation, but is very accurate due to the large step size. 
-}
circleArea :: Double -> Double
circleArea 0 = 0.0 -- The area of a circle with a radius of 0 is 0.0
circleArea r = let
    oneFourth = definiteIntegral 0 r (\x -> (((r*r) - (x*x)) ** 0.5)) 10000
    fullArea  = oneFourth * 4 -- Multiplies by 4 to get full approximation of area of circle
  in fullArea

{-
This function calculates the volume of a sphere. This is done by computing the area of a quarter
of a circle, and then multiplying that by 4 to get the full area, and then by (4r/3), because this is
the difference between volume of a sphere and area of a circle. Note, this is an approximation, 
but is very accurate due to the large step size. 
-}
sphereVolume :: Double -> Double
sphereVolume 0 = 0.0 -- The volume of a sphere with a radius of 0 is 0.0
sphereVolume r = let
    circleArea  = definiteIntegral 0 r (\x -> (((r*r) - (x*x)) ** 0.5)) 10000
    difference  = (4 * 4 * r) / 3 
    totalVolume =  difference * circleArea -- Multiplies the quarter area by 16r/3 to get the sphereVolume
  in totalVolume

{-

----------
TEST CASES
----------

Function: definiteIntegral
Test Case Number: 1
Input: definiteIntegral 2 7 (\x -> x^2) 10000
Expected Output: 111.667
Actual Output: 111.66666687509237

Function: definiteIntegral
Test Case Number: 2
Input: definiteIntegral 1 6 (\x -> x^3) 10000
Expected Output: 323.75
Actual Output: 323.750002187175

Function: definiteIntegral
Test Case Number: 3
Input: definiteIntegral 3 9 (\x -> x^4 + 5) 10000
Expected Output: 11791.2
Actual Output: 11791.200084223192

Function: circleArea
Test Case Number: 1
Input: circleArea 1
Expected Output: ~ 3.14
Actual Output: 3.1415914776116014

Function: circleArea
Test Case Number: 2
Input: circleArea 2
Expected Output: ~ 12.57
Actual Output: 12.566365910446406

Function: circleArea
Test Case Number: 3
Input: circleArea 3
Expected Output: ~ 28.27
Actual Output: 28.274323298489964

Function: sphereVolume
Test Case Number: 1
Input: sphereVolume 1
Expected Output: ~ 4.19
Actual Output: 4.1887886368154685

Function: sphereVolume
Test Case Number: 2
Input: sphereVolume 2
Expected Output: ~ 33.51
Actual Output: 33.51030909452375

Function: sphereVolume
Test Case Number: 3
Input: sphereVolume 3
Expected Output: ~ 113.1
Actual Output: 113.09729319395986

-}

{-
This property says that the area under the curve of the left side, should equal the area under the right side, when
using the origin as an argument. For example, f(-4) to f(0), on a function like x^2, should equal f(0) to f(4). The
tolerance range is set to 0.5 to accomdate really large 'x' values like 6634. A tolerance range like 1e-6 would work
just fine for 'x' values up to 5000 and then some, but not more than 6000.
Side Note: Replacing "definiteIntegral x 0" with "definiteIntegral 0 (-x)" yields the same result.
-}
integralProp1 x = let
    aEqualsX = definiteIntegral x 0 (\x -> x^2 + 1) 10000
    bEqualsX = definiteIntegral 0 x (\x -> x^2 + 1) 10000
    diff = bEqualsX - (negate aEqualsX)
    tol = 0.5
  in (abs diff <= tol)
testDefiniteIntegral1 = quickCheck integralProp1

{-
This property states that when approximating the area under the curve, having a large 'n' value will yield results that
are more accurate and smaller than having a small 'n' value. 
-}
integralProp2 (a,b) = let
    smallN = abs (definiteIntegral a b (\x -> x^2 + 1) 10)
    largeN = abs (definiteIntegral a b (\x -> x^2 + 1) 10000)
  in (smallN >= largeN)
testDefiniteIntegral2 = quickCheck integralProp2

{-
This property states that when approximating the area under a horizontal line, you can skip all steps and just subtract
'b' from 'a' and then multiply the result by 'b', and you'll get the same answer as integrating it.
Side Note: You can swap 'a' and 'b' in cond, and replace 'b' with 'a' in func's anonymous class, and still get the same result.
-}
integralProp3 (a,b,n) = let
    func = abs(definiteIntegral a b (\x -> b) n)
    cond = if n == 0 then 0.0 else abs((a - b) * b)
    test = func - cond
    tol = 1e-6
   in (test <= tol)
testDefiniteIntegral3 = quickCheck integralProp3

{-
This property also (indirectly) proves that when calculating the area under a horizontal line, the value of 'n' does not
matter as long as it is not 0; 'n' can be arbitrarily large (i.e. 10000) or small (1), and the answer will be the exact same.
Side note: Answers had to be rounded because floating point numbers cannot accurately be represented. The 'round' function
rounds to the nearest Integer, which is more than adequate for this property. 
-}
integralProp4 (a,b) = let
    lowestN  = round(abs(definiteIntegral a b (\x -> a) 1))
    lowN     = round(abs(definiteIntegral a b (\x -> a) 10))
    medN     = round(abs(definiteIntegral a b (\x -> a) 100))
    highN    = round(abs(definiteIntegral a b (\x -> a) 1000))
    highestN = round(abs(definiteIntegral a b (\x -> a) 10000))
  in (lowestN == lowN && lowN == medN && medN == highN && highN == highestN) 
testDefiniteIntegral4 = quickCheck integralProp4

{-

----------------
QUICKCHECK CASES
----------------

Function: integralProp1
Property: abs ((definiteIntegral 0 x (\x -> x^2 + 1) 10000) - (negate definiteIntegral x 0 (\x -> x^2 + 1) 10000)) <= 0.5
Actual Test Result: Passed (+++ OK, passed 100 tests)
*** Note: This function does fail on extremely large values like 12,0000 ***

Function: integralProp2
Property: (abs (definiteIntegral a b (\x -> x^2 + 1) 10)) >= (abs (definiteIntegral a b (\x -> x^2 + 1) 10000))
Actual Test Result: Passed (+++ OK, passed 100 tests)

Function: integralProp3
Property: (abs(definiteIntegral a b (\x -> b) n)) - (abs((a - b) * b)) <= 1e-6
Actual Test Result: Passed (+++ OK, passed 100 tests)

Function: integralProp4
Property: lowestN == lowN && lowN == medN && medN == highN && highN == highestN
Actual Test Result: Passed (+++ OK, passed 100 tests)

-}

{-

------------------------------------------
This is obsolete test code. Ignore please. 
------------------------------------------

integralProp5 (a,b,n) = let
    func = abs ((definiteIntegral a b (\x -> x) n)) 
  in (func >= 0)
testDefiniteIntegral5 = quickCheck integralProp5

sphereVolume :: Double -> Double
sphereVolume r = let
    a = circleArea r
    b = (4 * r) / 3
    c = a * b    
  in c

calculateMiddleX :: (Ord a, Num b, Num a) => a -> a -> (a -> b) -> a -> b
calculateMiddleX a bMinusZ g inverseZ = 
    if a < bMinusZ 
        then calculateMiddleX (a + inverseZ) bMinusZ g inverseZ
        else 0

-- middleX = 2 * (calculateMiddleX a (b - z) g (1 / z))

-}
