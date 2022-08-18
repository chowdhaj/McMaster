{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE NoMonomorphismRestriction #-}
module A4 where

-- The following are useful for the assignment
import Data.List (intersperse, nub)

-- Useful extra imports for the Bonus only
import qualified Data.Map as Map
import Control.Monad.Except
import Control.Monad.Reader

-- Here is the class that the assignment is all about: a representation
-- of boolean expressions with variables.
-- Note: 
-- 1) true is represented as 'andB []' 
-- 2) false as 'orB []'
-- 3) 'andB [e]' means the same as 'e', same with 'orB [e]'.
class BoolExpr repr where
  varB :: String -> repr
  notB :: repr -> repr
  andB :: [repr] -> repr
  orB :: [repr] -> repr
  impliesB :: repr -> repr -> repr
  xorB :: [repr] -> repr

-- Some useful test cases:
ex1, ex2, ex3, ex4, ex5 :: BoolExpr repr => repr
ex1 = andB [andB [], notB $ varB "x", orB [varB "y", varB "z"]]
ex2 = andB [andB [], notB $ varB "x", orB [varB "y", varB "z", varB "x"]]
ex3 = andB [andB [orB [varB "w"]]]
ex4 = andB [varB "w"]
ex5 = andB []
-- You should add more test cases, enough to cover all the 'corner' cases,
-- and then run them through all your examples.

-- Zeroeth Question: why is it justified for andB, orB and xorB to take lists
-- as input?  What does |xorB []| mean?

----------------------------------------------------------------------------
-- First interpretation: as a String.
newtype Pr = Pr {view :: String}

instance BoolExpr Pr where

-- Test case:
-- view ex2 should return the String
-- "(andB [(andB []),(notB var \"x\"),(orB [var \"y\",var \"z\",var \"x\"])])"
-- so that 'putStrLn $ view ex2' gives
-- (andB [(andB []),(notB var "x"),(orB [var "y",var "z",var "x"])])
-- Note that 'view' should not do any simplifications; even though ex3
-- and ex4 mean "the same", they will print differently.

----------------------------------------------------------------------------
-- Second interpretation: pulling out the (free) variables:
newtype FV = FV {fv :: [String]}

instance BoolExpr FV where

-- Test case:
-- fv ex2 should return exactly
-- [ "x", "y", "z" ]
-- Hint: Data.List.nub

----------------------------------------------------------------------------
-- Third interpretation: as 'syntax'
data BE = Var String | Not BE | And BE BE | Or BE BE | TrueB | FalseB
  deriving Show
asBE :: BE -> BE
asBE = id

-- Hint: this instance has more cases than the above
-- Hint: foldr1
instance BoolExpr BE where

-- Test cases:
-- asBE ex1
-- And TrueB (And (Not (Var "x")) (Or (Var "y") (Var "z")))
-- asBE ex2
-- And TrueB (And (Not (Var "x")) (Or (Var "y") (Or (Var "z") (Var "x"))))
-- asBE ex3
-- Var "w"

----------------------------------------------------------------------------
-- Fourth question: the other direction!
toBoolExpr :: BoolExpr repr => BE -> repr
toBoolExpr _ = undefined

ex1b, ex2b, ex3b, ex4b, ex5b :: BE
ex1b = And TrueB (And (Not (Var "x")) (Or (Var "y") (Var "z")))
ex2b = And TrueB (And (Not (Var "x")) (Or (Var "y") (Or (Var "z") (Var "x"))))
ex3b = Var "w"
ex4b = Var "s"
ex5b = TrueB

-- Part of this question: give an example that shows that you can
-- go in both directions (between BR and (BoolExpr repr => repr))
-- but that the translation is _not_ the identity.
-- [i.e. add some code here, and then something in 'main' below
--  that clearly demonstrates it]
-- Hint: depth will, in general, change.

----------------------------------------------------------------------------
-- Fifth question: compute the 'size' of an expression.
-- More precisely: every 'constructor' of the BoolExpr language counts
-- for 1.
-- size ex1 = 7
-- size ex2 = 8
-- size ex3 = 4
-- size ex4 = 2
newtype Size = Sz {size :: Int}

instance BoolExpr Size where

----------------------------------------------------------------------------
-- Sixth question: compute the 'depth' of an expression (as a tree)
-- except that varB counts as 0 depth.
-- depth ex1 = 2
-- depth ex2 = 2
-- depth ex3 = 3
-- depth ex4 = 1
-- Hint: maximum
newtype Depth = De {depth :: Int}

instance BoolExpr Depth where

-- Lastly, give an explicit example where going to BE and then back
-- to repr changes the depth of the results.

------------------------------------------------------------------------
-- Bonus questions
--

-- Bonus 1: implement a (potentially failing) evaluator from
-- a Valuation (an assignment of Bool to variables).

-- Use the following definitions:
type Valuation = Map.Map String Bool

newtype NotFound = VarNotFound String

newtype Eval = Ev { val :: ExceptT NotFound (Reader Valuation) Bool}

-- Hint: ask, liftEither, sequence, Data.Foldable.and, and monads
instance BoolExpr Eval where

-- For the rest of the bonus questions, the 'tutorial' at
-- http://okmij.org/ftp/tagless-final/index.html#course-oxford
-- contains a *lot* of useful advice. The most relevant is in
-- section 2, but section 3 and 4 are full of fascinating stuff too!
--
-- Bonus 2: implement another "printer" like that of Pr but minimize
-- the number of () in the results. 
--
-- Bonus 3: change BExpr so that it becomes possible to implement the CNOT
-- gate that is useful in quantum computing.
--  https://en.wikipedia.org/wiki/Controlled_NOT_gate
--
-- Bonus 4: implement an interpretation of BoolExpr that 
-- pushes all the 'notB' to be only on variables.
-- Hint: see push_neg in the tutorial.
--
-- Bonus 5: convert a BoolExpr to an equivalent BoolExpr that is in
-- https://en.wikipedia.org/wiki/Conjunctive_normal_form
--
-- Bonus 6: convert a BoolExpr to an equivalent BoolExpr that is in
-- https://en.wikipedia.org/wiki/Disjunctive_normal_form
--
-- Bonus 7: 'simplify' a BoolExpr.  Use the following logical
-- formulas to implement *generalized* simplifications
-- 1. true and x <-> x
-- 2. false or x <-> x
-- 3. x or x <-> x
-- 4. x and x <-> x
-- 5. false and y <-> false
-- 6. and & or are associative
------------------------------------------------------------------------
-- You can hand in a filled-in A5.hs (i.e. named that), or A5.lhs 
-- or A5.org.

------------------------------------------------------------------------
main :: IO ()
main = do
  let exs  = [ex1, ex2, ex3, ex4, ex5]
  let exbs = [ex1b, ex2b, ex3b, ex4b, ex5b]
  putStrLn $ show $ map depth exs
  -- [2,2,3,1,1]
  putStrLn $ show $ map size exs
  -- [7,8,4,2,1]
  putStrLn $ show $ map view exs
  -- ["(andB [(andB []),(notB var \"x\"),(orB [var \"y\",var \"z\"])])","(andB [(andB []),(notB var \"x\"),(orB [var \"y\",var \"z\",var \"x\"])])","(andB [(andB [(orB [var \"w\"])])])","(andB [var \"s\"])","(andB [])"]

  putStrLn $ show $ map fv exs
  -- [["x","y","z"],["x","y","z"],["w"],["s"],[]]
  putStrLn $ show $ map asBE exs
  -- [And TrueB (And (Not (Var "x")) (Or (Var "y") (Var "z"))),And TrueB (And (Not (Var "x")) (Or (Var "y") (Or (Var "z") (Var "x")))),Var "w",Var "s",TrueB]
  putStrLn $ show $ map view $ map toBoolExpr exbs
  -- ["(andB [(andB []),(andB [(notB var \"x\"),(orB [var \"y\",var \"z\"])])])","(andB [(andB []),(andB [(notB var \"x\"),(orB [var \"y\",(orB [var \"z\",var \"x\"])])])])","var \"w\"","var \"s\"","(andB [])"]
