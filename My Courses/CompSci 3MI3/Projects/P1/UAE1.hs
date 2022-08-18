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
-- This is the old data type for Term
data Term = IsZero Term
          | Pred Term
          | Succ Term
          | If Term Then Term Else Term
          | ZERO
          | FALSE
          | TRUE
    deriving (Show, Eq)
-}

{-
Question:
We will need to begin by creating two more data types, to represent
both values and numeric values. Remove the value terms from your term
data type, and create two new ones, conforming to the grammar given
above. This will become important later on in the project.

Depending on how you set this up, you may cause a naming conflict
between the successor function already defined in your term datatype
and your new datatype for numeric values. If this is the case, rename
the successor function in the numeric values datatype. We will need
to add an inference rule to the ones given above.
-}

{-
Note: All data types derive Show and Eq
-}

-- This is the data type for Value; it can be either Trues or Falses
-- The values mimic (constant) true and (constant) false (in Haskell)
data Values = Trues | Falses
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
Next write a Haskell function which encodes the small-step operational
semantics given above. This function should accept an argument of the
term type, and produce an output also of the term type. Call this
function ssos, which stands for small-step opeartional semantics.

Just as your data type for terms should not have any of Haskell’s
native data types in it (like boolean truth values or numbers),
neither should your function. Points will be deducted for using
Haskell’s native types.

In addition to the rules above, please add rules which cause all
values to evaluate to themselves (i.e., add reflexivity for values,
both boolean and numeric). This will be necessary later on.
-}

-- The evaluation rules for "ssos" are defined below
-- Note: "ssos" stands for small-step operational semantics

ssos :: Term -> Term

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

-- E-Succ
ssos (Successor term) = Successor (ssos (term))

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

{-
Question:
Now that we have our small-step semantics roughed out, write a
function to evaluate our terms, called eval. This function should
repeatedly apply the single-step semantic to a term until the term
can’t be evaluated further. How to figure out when a term can’t be
evaluated further is left as an exercise to the student.
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
