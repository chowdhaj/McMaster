{-

Name         : Jatin Chowdhary
Student ID   : 400033011
Date         : November 3rd, 2017
Assignment 3 : Polynomials

-}

module Polynomial where

data Poly =
    X
    | Coef Integer
    | Sum Poly Poly
    | Prod Poly Poly
    deriving Show

{- 
The function 'polyCoefficients' gets the coefficients of the standard polynomial form [i.e. 4x^2 + 69x + 420],
and returns it in a list of Integers [i.e. 4, 69, 420]. It accepts 'Poly' and returns [Integers].
-}
polyCoefficients :: Poly -> [Integer]
polyCoefficients X            = [0, 1]
polyCoefficients (Coef c)     = [c]
polyCoefficients (Sum s1 s2)  = polyAddCoef (polyCoefficients s1) (polyCoefficients s2)
polyCoefficients (Prod p1 p2) = polyProdCoef (polyCoefficients p1) (polyCoefficients p2)

{-
The function 'polyProdCoef' calculates the PRODUCT of two lists of cofficients. It takes two Integer lists,
and returns a list of Integers. 
-}
polyProdCoef :: [Integer] -> [Integer] -> [Integer]
polyProdCoef n m       = go [] n m where
    go acc (x:xs) ys   = go (polyAddCoef (map (x * ) ys) acc) xs (0:ys)
    go acc [] _        = acc

{-
The function 'polyAddCoef' calculates the SUM of two lists of of cofficients by calling the function 'polyZip'. 
It takes two Integer lists, and returns a list of Integers. 
-}
polyAddCoef :: [Integer] -> [Integer] -> [Integer]
polyAddCoef = polyZip (+)

{-
This function act identical to the regular 'length' function in Prelude. However, 'polyLength' is modified for Integers,
because 'length' returns an 'Int', and I need 'Integer'.
-}
polyLength :: [a] -> Integer
polyLength (n:ns) = polyLength ns + 1
polyLength _      = 0

{-
The function 'polyZip' is a modified version of 'zipWith', which calculates the sum/product of elements occuring 
in the same position in two lists.
-}
polyZip :: (Integer -> Integer -> Integer) -> [Integer] -> [Integer] -> [Integer]
polyZip g (x:xs) (y:ys)   = g x y : polyZip g xs ys
polyZip g _ (y:ys)        = g 0 y : polyZip g [] ys
polyZip g (x:xs) _        = g x 0 : polyZip g xs []
polyZip g _ _             = []

{-
The function 'polyValue' sticks 'x' into 'X' and returns the evaluation. In other words, it calculates the y-coord of a function,
given the x-coord. It takes Poly and an Integer, and returns an Integer.
-}
polyValue :: Poly -> Integer -> Integer
polyValue X x            = x
polyValue (Coef c) _     = c
polyValue (Sum s1 s2) x  = polyValue s1 x + polyValue s2 x
polyValue (Prod p1 p2) x = polyValue p1 x * polyValue p2 x

{-
This function returns the degree of a polynomial. It accepts Poly and returns an Integer.
-}
polyDegree :: Poly -> Integer
polyDegree = polyLength . dropWhile ( == 0) . reverse . tail . polyCoefficients

{-
This function calculates the derivative of a polynomail. It accepts Poly (the function), 
and returns Poly (the derivative).
-}
polyDeriv :: Poly -> Poly
polyDeriv X            = Coef 1
polyDeriv (Coef _)     = Coef 0
polyDeriv (Sum s1 s2)  = Sum (polyDeriv s1) (polyDeriv s2)
polyDeriv (Prod p1 p2) = Sum (Prod (polyDeriv p1) p2) (Prod p1 (polyDeriv p2))

{-
Function: polyValue
Test Case Number: 1
Input: (Sum (Prod X X) (Coef 3)) 2
Expected Output: 7
Actual Output: 7

Function: polyValue
Test Case Number: 2
Input: (Sum (Prod X X) (Coef 5)) 7
Expected Output: 54
Actual Output: 54

Function: polyValue
Test Case Number: 3
Input: (Prod (Coef 2) X) 4
Expected Output: 8
Actual Output: 8

Function: polyDegree
Test Case Number: 1
Input: (Prod (Coef 2) X)
Expected Output: 1
Actual Output: 1

Function: polyDegree
Test Case Number: 2
Input: (Sum (Prod X X) (Coef 5))
Expected Output: 2
Actual Output: 2

Function: polyDegree
Test Case Number: 3
Input: (Prod (Prod X X) X)
Expected Output: 3
Actual Output: 3

Function: polyDeriv
Test Case Number: 1
Input: (Prod (Prod X X) X)
Expected Output: (Prod (Prod X X) (Coef 3))
Actual Output: Sum (Prod (Sum (Prod (Coef 1) X) (Prod X (Coef 1))) X) (Prod (Prod X X) (Coef 1))

Function: polyDeriv 
Test Case Number: 2
Input: (Sum (Prod X X) (Coef 5))
Expected Output: (Sum (Prod (Coef 1) X) (Prod (Coef 1) X))
Actual Output: Sum (Sum (Prod (Coef 1) X) (Prod X (Coef 1))) (Coef 0)

Function: polyDeriv 
Test Case Number: 3
Input: (Prod (Coef 2) X)
Expected Output: (Coef 2)
Actual Output: Sum (Prod (Coef 0) X) (Prod (Coef 2) (Coef 1))

* NOTE: THERE ARE MANY WAYS TO DO POLYDERIV, HENCE MY EXPECTED OUTPUT =/= ACTUAL OUTPUT *
-}