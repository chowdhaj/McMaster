module Matching where

import Data.Char (digitToInt, isAlpha, isDigit, isSpace)
import Data.List (partition)
import Expr
import Law
import Parser

-- | Substitutions
type Subst = [(VarName, Expr)]

-- Yields the expression associated with a given variable in a substitution if exists
-- otherwise returns the variable itself
-- binding [("x", f)] "x" = f
-- binding [("y", zip(f, g)), ("z", f . g)] "x" = Var "x"
binding :: Subst -> VarName -> Expr
binding [] v = Var v
binding ((u, e) : s) v = if u == v then e else binding s v

-- Apply a substitution to an expression.
-- Example:
-- applySubst [("x", pair(a, b)), ("y", fst)] (x . y) = pair (a, b) . fst
-- applySubst [("x", this), ("y", that)] (fst . snd) = fst . snd
--   where x = Var "x"
--         y = Var "y"
applySubst :: Subst -> Expr -> Expr
applySubst s (Var v) = binding s v
applySubst s (Con f xs) = todo "applySubst1"
applySubst s (Compose xs) = todo "applySubst2"

-- Yield all partitions of a sequence into a list of ‘m’ subsequences,
-- Don't allow empty subsequence if the sequence is not empty
-- Why the result of type is [[[a]]]:
--   * [a] is the type of subsequence
--   * [subsequence] = [[a]] type of partition - the list of subsequence
--   * [partition] = [[[a]]] type of partitions list
-- Example:
-- > parts 2 [1, 2, 3, 4]
-- [ [ [1] , [2,3,4] ]
-- , [ [1,2] , [3,4] ]
-- , [ [1,2,3] , [4] ]
-- ]
parts :: Int -> [a] -> [[[a]]]
-- Base case
parts 0 [] = [[]]
parts 0 xs = []
-- No partitions of empty sequence into m > 0 components.
parts m [] = []
parts m (x : xs) = case1 ++ case2
  where
    -- Case 1: x alone in the partition
    case1 = todo "case1"
    -- Case 2: x in the same partition with adjacent elements
    case2 = todo "case2"

-- match a pattern against an expressions, return a list of substitutions
-- Why a [Subst] instead of Subst? Because a pattern can match an expression in different ways
-- Example:
-- > match (parseExpr "a . b") (parseExpr "f . g . h . zip (x , y)")
-- [ [('b',g . h . zip(x, y)),('a',f)]
-- , [('b',h . zip(x, y)),('a',f . g)]
-- , [('b',zip(x, y)),('a',f . g . h)]
-- ]
match :: Expr -> Expr -> [Subst]
match = xmatch []

-- Helper for `match`, whereas the first argument can be thought of as "base" substitutions,
-- where later matches can be built upon
-- Example:
-- > xmatch [('x', parseExpr "g . h"), ('y', parseExpr "f")] (Var 'x') (parseExpr "t")
-- [] --- ('x' can not refer to different exprs)
-- > xmatch [('x', parseExpr "g . h"), ('y', parseExpr "f")] (Var 'x') (parseExpr "g . h")
-- [[('x', g . h), ('y', f)]] --- ('x' refers to the same expr)
xmatch :: Subst -> Expr -> Expr -> [Subst]
-- Matching a variable e against an arbitrary expression
xmatch base (Var v) e
  -- if `v` didn't match with anything, then success and `v` points to `e`
  | binding base v == Var v = [(v, e) : base]
  -- if `v` already pointed to the same expr, then success with the same substitutions
  | binding base v == e = [base]
  -- otherwise, same variable cannot point to different expressions, thus no substitution makes sense
  | otherwise = []
-- Matching a constant against a variable or composition always fails.
xmatch _ (Con _ _) (Var v) = []
xmatch _ (Con _ _) (Compose ys) = []
-- Matching a constant against the *same* constant succeeds if corresponding elements
-- in the two argument lists can be matched.
xmatch base (Con f patterns) (Con g exprs) = if f == g then xmatchlist base (zip patterns exprs) else []
-- Matching a composition against a variable or constant fails because
-- ‘Compose xs’ is a valid expression only when ‘length xs ≥ 2’.
xmatch _ (Compose _) (Var _) = []
xmatch _ (Compose _) (Con _ _) = []
-- Matching two sequences of compositions succeeds if matching appropriately
-- aligned segments does.
xmatch base (Compose patterns) (Compose exprs) = concatMap (xmatchlist base) (alignCompose patterns exprs)
  where
    -- Different ways to align a list of composed patterns against a list of composed expressions
    -- Example:
    -- > alignCompose [x, y] [f, zip (a, b), h]
    -- [ [(x,f) , (y,zip (a, b) . h)]
    -- , [(x,f . zip (a, b)) , (y,h)]
    -- ]
    -- After finding such alignments we can try to match `x against f, y against zip (a, b) . h`
    -- or `x against f . zip (a,b), y against h`
    alignCompose :: [Expr] -> [Expr] -> [[(Expr, Expr)]]
    alignCompose patterns exprs = [zip patterns (map compose zs) | zs <- parts (length patterns) exprs]

-- Like `match`, but with a list of (pattern, expressions)
-- from a "base" substitutions, match a list of patterns against a list of expressions
xmatchlist :: Subst -> [(Expr, Expr)] -> [Subst]
xmatchlist base [] = [base]
xmatchlist base ((pattern, expr) : pes) = concat [xmatchlist nxtBase pes | nxtBase <- xmatch base pattern expr]

