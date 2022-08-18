module Rewriting where

import Data.Char (digitToInt, isAlpha, isDigit, isSpace)
import Data.List (partition)
import Expr
import Law
import Parser
import Matching

-- | Location of a subexpression w.r.t it's parent
-- This is useful e.g, when we want to replace a subexpression inside an expression
data Location
  = -- `All` refers to the whole expression
    All
  | -- ‘Seg i l` is the composition segment of length l beginning at position i (0-index)
    -- E.g: expr = Compose [f, zip, g, h], then
    -- `Seg 2 2` refers to `Compose [g, h]`
    -- `Seg 0 3` refers to `Compose [f, zip, g]`
    Seg Int Int
  | -- `Arg i loc` goes to i-th argument (0-index), then keeps going to location `loc` of that argument.
    -- E.g: expr = Con "mul" [f, g, h, Compose [x, y, z], m] then
    --  `Arg 3 (Seg 0 2)` refers to `Compose [x, y]`
    --  `Arg 0 All` refers to `f`
    Arg Int Location
  deriving (Show)

-- Subexpression in their parent expressions.
data SubExpr
  = SubExpr
      Expr -- The subexpression
      Location -- Location of the subexpression w.r.t its parent

instance Show SubExpr where
  show (SubExpr e loc) = "subexpression " ++ show e ++ " located at " ++ show loc

-- | All SubExprs of a given expression
-- Example
-- > e = parseExpr "f . g . zip (m . n, p . q)"
-- > subExprs e
-- subexpression f . g . zip(m . n, p . q) located at All
-- subexpression f . g                     located at Seg 0 2
-- subexpression g . zip(m . n, p . q)     located at Seg 1 2
-- subexpression f                         located at Arg 0 All
-- subexpression g                         located at Arg 1 All
-- subexpression zip(m . n, p . q)         located at Arg 2 All
-- subexpression m . n                     located at Arg 2 (Arg 0 All)
-- subexpression m                         located at Arg 2 (Arg 0 (Arg 0 All))
-- subexpression n                         located at Arg 2 (Arg 0 (Arg 1 All))
-- subexpression p . q                     located at Arg 2 (Arg 1 All)
-- subexpression p                         located at Arg 2 (Arg 1 (Arg 0 All))
-- subexpression q                         located at Arg 2 (Arg 1 (Arg 1 All))
-- Hint: you might want to have two auxiliary function:
-- args :: [Expr] -> [SubExpr], used for both Con and Compose
-- segments :: [Expr] -> [SubExpr], used for Compose
subExprs :: Expr -> [SubExpr]
subExprs = todo "subExprs"


-- | Replacing a subexpression of expression ~e~ at a location ~loc~ with a replacement expression ~r~.
-- Note that we assume the location is valid w.r.t the expression, i.e
-- `map location (subExprs e)` contains `loc`
-- Example
-- > e = parseExpr "f . g . h . zip (m . n, mul)"
-- (e has subexpression m . n located at Arg 3 (Arg 0 All))
-- > replace e (Arg 3 (Arg 0 All)) (parseExpr "mul . add")
-- f . g . h . zip(mul . add, mul)
replace :: Expr -> Location -> Expr -> Expr
replace e All replacement = replacement
replace (Con f xs) (Arg j loc) y = todo "replace1"
replace (Compose xs) (Arg j loc) y = todo "replace2"
replace (Compose xs) (Seg j k) y = todo "replace3"

-- | Given a pair of laws and an expression `e`, returns all possible pair way of rewriting `e`
-- The result is the list of (LawName, Expr), where LawName is the name of the applicable law, and
-- Expr is the result of applying LawName to `e`.
rewrite :: ([Law], [Law]) -> Expr -> [(LawName, Expr)]
rewrite (llaws, rlaws) x = concat $ [applyLaw law sx x | law <- llaws, sx <- subExprs x] ++ [applyLaw law sx x | law <- rlaws, sx <- subExprs x]
  where
    applyLaw :: Law -> SubExpr -> Expr -> [(LawName, Expr)]
    applyLaw (Law name lhs rhs) (SubExpr sub loc) exp = todo "applyLaw"

-- | Simply choose the first rewriting, and repeat the process until can't rewrite anymore
--
repeatedly :: (Expr -> [(LawName, Expr)]) -> Expr -> [Step]
repeatedly rw current = case rw current of
  (name, next) : _ -> (name, next) : repeatedly rw next
  [] -> []

-- | Calculate: repeatedly applying laws to rewrite expression
--
calculate :: ([Law], [Law]) -> Expr -> Calculation
calculate pls x = (x, repeatedly (rewrite pls) x)

-------------------------------------------------------------------------------
prove :: [Law] -> String -> String
prove laws = printCalc . proveEqn laws . parseEqn

proveEqn :: [Law] -> (Expr, Expr) -> Calculation
proveEqn laws (lhs, rhs) = paste (calculate (basic, others) lhs) (calculate (basic, others) rhs)
  where
    (basic, others) = partition basicLaw laws

