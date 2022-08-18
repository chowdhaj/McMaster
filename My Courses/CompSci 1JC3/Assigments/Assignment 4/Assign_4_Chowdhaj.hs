{-
Name: Jatin Chowdhary
MacID: Chowdhaj
Date: November 18th, 2017
Assignment 4
-}

module PolynomialList where

import Test.QuickCheck

data Poly =
    X |
    Coef Integer |
    Sum Poly Poly |
    Prod Poly Poly
    deriving (Show)

-- This function removes trailing zeros at the end of a list. For example: [1,1,1,0,0,0] --> [1,1,1]
-- It accomplishes this by reversing the list, then dropping all zeros, and then reversing the list again
cleanPolyList :: [Integer] -> [Integer]
cleanPolyList = reverse . dropWhile (== 0) . reverse

-- This function is a modified version of 'zipWith', which calculates the sum/product of elements...
-- ... occuring in the same position in two lists. This was used in Assignment 3
polyZip :: (Integer -> Integer -> Integer) -> [Integer] -> [Integer] -> [Integer]
polyZip g (x:xs) (y:ys)   = g x y : polyZip g xs ys
polyZip g (x:xs) _        = g x 0 : polyZip g xs []
polyZip g _ (y:ys)        = g 0 y : polyZip g [] ys
polyZip g _ _             = []

-- This function retrieves numbers from a file, and then puts those numbers in a list of Integers
-- It also cleans the list of Integers, by removing any trailing zeros at the end
getPolyList :: FilePath -> IO [Integer]
getPolyList path = 
    readFile path >>=
    return . cleanPolyList . map (read :: String -> Integer) . lines

-- This function returns the value of 'n' at polynomial 'pl' using Horners method
polyListValue :: [Integer] -> Integer -> Integer
polyListValue pl n = let
    horners elem x = elem + x * n
  in (foldr1 horners pl)

-- This function returns the degree of a polynomial List, where the degree is basically...
-- ... the length and 0 is undefined
polyListDegree :: [Integer] -> Integer
polyListDegree x = if degree == 0 then error "Undefined" else degree 
    where
        degree = fromIntegral . length . cleanPolyList $ x

-- This function returns the derivative of a polynomial List. It multiplies the...
-- ... infinite list from the back the polynomial list
polyListDeriv :: [Integer] -> [Integer]
polyListDeriv = cleanPolyList . zipWith (*) [1..] . reverse

-- This function takes two polynomial lists and adds them together
polyListSum :: [Integer] -> [Integer] -> [Integer]
polyListSum pl ql = cleanPolyList $ polyZip (+) pl ql

-- This function takes two polynomial lists and returns the product
polyListProd :: [Integer] -> [Integer] -> [Integer]
polyListProd pl ql = cleanPolyList $ go [] pl ql 
    where
        go acc _ [] = acc
        go acc ys (x:xs) = go (polyListSum (map (x*) ys) acc) (0:ys) xs

{-

Function: getPolyList
Test Case Number: 1
Input: "/Users/Admin/Desktop/hs.txt"
Expected Output: [1,2,3,4]
Actual Output: [1,2,3,4]

Function: getPolyList
Test Case Number: 2
Input: "/Users/Admin/Desktop/test.txt"
Expected Output: [5,6,7]
Actual Output: [5,6,7]

Function: getPolyList
Test Case Number: 3
Input: "/Users/Admin/Desktop/haska.txt"
Expected Output: [9,9,9]
Actual Output: [9,9,9]

Function: polyListValue
Test Case Number: 1
Input: [1,2,3] 1
Expected Output: 6
Actual Output: 6

Function: polyListValue
Test Case Number: 2
Input: [5,6,7] 1
Expected Output: 18
Actual Output: 18

Function: polyListValue
Test Case Number: 3
Input: [2,4,6] 1
Expected Output: 12
Actual Output: 12

Function: polyListDegree
Test Case Number: 1
Input: [1,2]
Expected Output: 2
Actual Output: 2

Function: polyListDegree
Test Case Number: 2
Input: [4,5,6,7]
Expected Output: 4
Actual Output: 4

Function: polyListDegree
Test Case Number: 3
Input: [1,0,0,1]
Expected Output: 4
Actual Output: 4

Function: polyListDeriv
Test Case Number: 1
Input: [1,2]
Expected Output: [2,2]
Actual Output: [2,2]

Function: polyListDeriv
Test Case Number: 2
Input: [1,2,3]
Expected Output: [3,4,3]
Actual Output: [3,4,3]

Function: polyListDeriv
Test Case Number: 3
Input: [1,0,0,4] 
Expected Output: [4,0,0,4]
Actual Output: [4,0,0,4]

Function: polyListSum
Test Case Number: 1
Input: [1,2,3] [4,5,6]
Expected Output: [5,7,9]
Actual Output: [5,7,9]

Function: polyListSum
Test Case Number: 2
Input: [1,1,1] [2,2,2]
Expected Output: [3,3,3]
Actual Output: [3,3,3]

Function: polyListSum
Test Case Number: 3
Input: [2,1,0,1] [2,1,0,1]
Expected Output: [4,2,0,2]
Actual Output: [4,2,0,2]

Function: polyListProd
Test Case Number: 1
Input: [2,3] [4,3]
Expected Output: [8,18,9]
Actual Output: [8,18,9]

Function: polyListProd
Test Case Number: 2
Input: [4] [4,5]
Expected Output: [16,20]
Actual Output: [16,20]

Function: polyListProd
Test Case Number: 3
Input: [9,10,11] [7]
Expected Output: [63,70,77]
Actual Output: [63,70,77]

-}

polyListValueProp pl = (polyListValue pl 1) == sum pl
testMyPolyListValuePro = quickCheck polyListValueProp

{-

Function: polyListValue
Property: (polyListValue pl 1) == sum pl
Actual Test Result: *** Failed! Exception: 'Prelude.foldr1: empty list'

-}
