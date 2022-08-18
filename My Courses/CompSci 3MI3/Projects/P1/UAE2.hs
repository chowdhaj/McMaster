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
Question:
In addition, you will need to add some more evaluation rules so that
the following requirements are met. You are required to use the
small-step semantic style to deal with these problems. (You can’t
just call error!):
    * If, during normal execution, a wrong value is produced, the
      entire expression should evaluate to wrong.
    * You may need to add one or two additional rules to make your
      wrong term work the same way as the other values.
-}

-- The evaluation rules for "ssos" are defined below
-- Note: "ssos" stands for small-step operational semantics

ssos :: Term -> Term

-- E-If-Wrong
ssos (If (NMVL someNumVal) Then term_2 Else term_3) = VL Wrong

-- E-If-Wrong-Equals-Wrong
ssos (If (VL Wrong) Then _ Else _) = VL Wrong
-- If the term evaluates to Wrong, then it doesn't matter what the
-- rest of the statement is, the whole thing is still Wrong, and
-- stays Wrong; I hope that makes sense

-- E-If-Then-Wrong-Equals-Wrong
ssos (If _ Then (VL Wrong) Else _) = VL Wrong
-- If the "Then" evaluates to Wrong, then the whole thing is still
-- Wrong, and stays Wrong; I hope that makes sense

-- E-If-Then-Else-Wrong-Equals-Wrong
ssos (If _ Then _ Else (VL Wrong)) = VL Wrong
-- If the "Else" evaluates to Wrong, then the whole thing is still
-- Wrong, and stays Wrong; I hope that makes sense

{- Note: Everything else is from `UAE1.hs`, and remains the same -}

-- E-IfTrue
ssos (If (VL Trues) Then term Else _) = term
-- Note: You can think of "term" as "t", as per UAE

-- E-IfFalse
ssos (If (VL Falses) Then _ Else term) = term
-- Note: You can think of "term" as "t", as per UAE

-- E-If
ssos (If term_1 Then term_2 Else term_3) =
    (If (ssos(term_1)) Then term_2 Else term_3)
-- Note: You can think of "term_#" as "t#", as per UAE

--E-Succ-Wrong
ssos (Successor (VL _)) = VL Wrong
-- The successor of any Value is Wrong; semantically this makes sense
-- Successor True  => Wrong
-- Successor False => Wrong

-- E-Succ
ssos (Successor term) = Successor (ssos (term))

-- E-Pred-Wrong
ssos (Predecessor (VL _)) = VL Wrong
-- The predecessor of any Value is Wrong; semantically this makes
-- sense, and it is just like Successor of any Value
-- Predecessor True  => Wrong
-- Predecessor False => Wrong

{- Note: Everything else is from `UAE1.hs`, and remains the same -}

-- E-PredZero
ssos (Predecessor (NMVL Zero)) = NMVL (Zero)
-- Basically, what we are saying is:
-- ssos (Predecessor (Zero)) = (Zero)
-- The predecessor of 0 is 0

-- E-PredSucc
ssos (Predecessor (Successor (NMVL someNumVal))) = NMVL someNumVal
-- The following is the same as the above; I added it for fun
--ssos (Successor (Predecessor (NMVL someNumVal))) = NMVL someNumVal

-- E-PredSucc
ssos (Predecessor (NMVL (SuccNV someNumVal))) = NMVL someNumVal

-- E-Pred
ssos (Predecessor term) = Predecessor (ssos(term))

-- E-IsZeroIsZero
ssos (ZeroTest (NMVL Zero)) = VL Trues

-- E-IsZeroSucc
ssos (ZeroTest (Successor (NMVL someNumVal))) = VL Falses
-- The successor of any non-zero is false or falses according to UAE

-- E-IsZeroSucc
ssos (ZeroTest (NMVL (SuccNV someNumVal))) = VL Falses
-- The successor of any non-zero is false or falses according to UAE

-- E-IsZero
ssos (ZeroTest (term)) = ZeroTest (ssos(term))

-- Reflexivity, or reflexive evaluations, are defined below:
-- As per convention, the values evaluate to themselves

-- Numeric Value Zero
ssos (NMVL Zero) = NMVL Zero

-- Falses (False)
ssos (VL Falses) = VL Falses

-- Trues (True)
ssos (VL Trues) = VL Trues

-- Numeric Value Successor
ssos (NMVL (SuccNV someNumVal)) = NMVL (SuccNV someNumVal)

-- Wrong will always evaluate to Wrong
ssos (VL Wrong) = VL Wrong

{-
The `eval` function and the test cases are the same from `UAE1.hs`;
nothing has been changed. With the addition of the Wrong Value,
something like `testCase3` should evalulate to Wrong, because Trues
(or Falses) is/are not Zero, nor is/are it/they a numeric value
-}

eval :: Term -> Term
eval someLongTerm =
    if (ssos (someLongTerm)) == someLongTerm
        then someLongTerm
            else eval(ssos (someLongTerm))


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
