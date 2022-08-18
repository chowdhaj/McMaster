{-
AUTHOR  :: Jatin Chowdhary
MACID   :: Chowdhaj
LICENSE :: GPL(e)
-}

import System.IO
import Data.List

-- I added this for testing purposes; to make sure that the Haskell
-- file compiles successfully. If it causes trouble for you, please
-- remove it, or comment it out via double hyphens: "--"
main :: IO ()
main = return ()

{-
Note: All data types derive Show and Eq
-}

{-
Question:
Let’s add a new value, wrong, which will be the result of evaluating
nonsense terms, like the one above. The following is an incomplete
set of the rules needed to implement wrong. In the following, V will
be the set of values, as defined in the grammar above, and NV will be
the set of numeric values, as defined above.
-}

-- This is the data type for Value; it can be either Trues or Falses
-- The values mimic (constant) true and (constant) false (in Haskell)
-- A new value, "Wrong" is added to deal with wrongness
data Values = Trues | Falses | Wrong
    deriving (Show, Eq)

-- This is the data type for NumericValue, as per UAE
-- The values are Zero and the successor of a numeric value
data NumericValue = Zero | SuccNV NumericValue
    deriving (Show, Eq)

-- This is the data type for Then
data Thens = Then
    deriving (Show, Eq)

-- This is the data type for Else
data Elses = Else
    deriving (Show, Eq)

-- This is the new data type for Term; it removes the value terms
-- from the old data type Term
data Term = ZeroTest Term
          | Predecessor Term
          | Successor Term
          | If Term Thens Term Elses Term
          | VL Values
          | NMVL NumericValue
    deriving (Show, Eq)

{-
The evaluation rules for "bsos" are defined below
Note: "bsos" stands for big-step operational semantics
-}

bsos :: Term -> Term

-- B-Value
bsos (VL someValue) = VL someValue
bsos (NMVL someNumericValue) = NMVL someNumericValue

-- B-IfTrue && B-IfFalse

bsos (If term_1 Then term_2 Else term_3)
    -- If term_1 evaluates to Trues, then term_2
    | bsos(term_1) == (VL Trues) = bsos(term_2)
    -- If term_1 evaluates to Falses, then term_3
    | bsos(term_1) == (VL Falses) = bsos(term_3)
    -- Anything else and throw a Wrong (kind of like Error)
    | otherwise = VL Wrong

{-
-- Tried something different, didn't work out because I was using
-- "where" the wrong way. I got it to work in the end, but it was
-- horrible code, in terms of style and readability
bsos term_1 term_2 term_3 = 
    where term_1 = if bsos (term_1) == (VL Trues)
                       then bsos (term_2)
                           else VL Wrong
          term_2 = if bsos (term_1) == (VL Falses)
                       then bsos (term_3)
                           else VL Wrong
          term_3 = VL Wrong

-- Ignore this:
-- where isEven x = if even x then x else x - 1
-}

-- B-Succ
bsos (NMVL someNumericValue) = NMVL (SuccNV someNumericValue)
bsos (VL someValue) = VL Wrong

-- B-PredSucc && B-PredZero
bsos (NMVL Zero) = NMVL Zero
bsos (NMVL (SuccNV someNumericValue)) = NMVL someNumericValue
bsos term_prime = VL Wrong

-- B-IsZeroSucc && B-IsZeroZero
bsos (NMVL Zero) = VL Trues
bsos (NMVL (SuccNV someNumericValue)) = VL Falses
bsos term_prime = VL Wrong

{-
The `eval` function and the test cases are the same from `UAE1.hs`;
nothing has been changed. With the addition of the Wrong Value,
something like `testCase3` should evalulate to Wrong, because Trues
(or Falses) is/are not Zero, nor is/are it/they a numeric value
-}

eval :: Term -> Term
eval someLongTerm =
    if (bsos (someLongTerm)) == someLongTerm
        then someLongTerm
            else eval(bsos (someLongTerm))

-- Test Cases (Provided By Dr. Moore)
testCase1 :: Term
testCase1 =
    Predecessor $ Successor $ Successor $ Successor $
        Predecessor $ Predecessor $ Successor $ Successor $
            Successor $ NMVL Zero

testCase2 :: Term
testCase2 =
    If (ZeroTest (Successor (NMVL Zero)))
        Then (VL Trues)
            Else (Successor (NMVL (Zero)))

testCase3 :: Term
testCase3 = ZeroTest (VL Trues)
