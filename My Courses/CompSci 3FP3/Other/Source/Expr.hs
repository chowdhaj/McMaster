module Expr where

import Data.Char (digitToInt, isAlpha, isDigit, isSpace)
import Parser
-------------------------------------------------------------------------------
-- | Expression
-- Our convention:
-- - single-letter names denote variables
-- - multi-letter names denote constants.
type VarName = Char

type ConName = String

data Expr
  = Var VarName
  | Con ConName [Expr]
  | Compose [Expr]
  deriving (Eq)

-- fst . pair(f . fst, g . snd) . zip
exprExample :: Expr
exprExample =
  Compose
    [ fst,
      Con "pair" [Compose [Var 'f', fst], Compose [Var 'g', snd]],
      Con "zip" []
    ]
  where
    fst = Con "fst" []
    snd = Con "snd" []

instance Show Expr where
  show = printExpr

printExpr :: Expr -> String
printExpr (Var v) = [v]
printExpr (Con f xs)
  | null xs = f
  | simple xs = f ++ " " ++ printExpr (head xs)
  | otherwise = f ++ "(" ++ foldl1 (\x y -> x ++ ", " ++ y) (map printExpr xs) ++ ")"
printExpr (Compose xs) = foldl1 (\x y -> x ++ " . " ++ y) (map printExpr xs)

-- Will only be applied to nonempty lists.
-- If compose returns `Compose xs`, then it should satisfy the following property:
--    * length xs >= 2
--    * xs itself has no element in the form `Compose ys`
-- Example:
-- compose [Var 'x'] = Var 'x'
-- compose [Con "zip" [x, y]] = Con "zip" [x, y]
-- compose [a, b] = Compose [a, b]
-- compose [Compose [a, b], Compose [c, d, e], d, e] = Compose [a, b, c, d, e, d, e]
compose :: [Expr] -> Expr
compose xs = todo "compose"

-- | Our `complexity` is defined to be the number of composed functions
complexity :: Expr -> Int
complexity (Var v) = 1
complexity (Con f es) = 1
complexity (Compose es) = length es

-- | Helper functions
simple :: [Expr] -> Bool
simple xs = singleton xs && simpleton (head xs)

simpleton :: Expr -> Bool
simpleton (Var v) = True
simpleton (Con f es) = null es
simpleton (Compose es) = False

singleton :: [a] -> Bool
singleton [_] = True
singleton _ = False

-------------------------------------------------------------------------------

-- | Parsing
letter :: Parser Char
letter = sat isAlpha

space :: Parser String
space = many (sat isSpace)

-- Skip whitespace around a parser.
token :: Parser a -> Parser a
token p = do
  space
  x <- p
  space
  return x

-- Parse a given string
string :: String -> Parser String
string "" = return ""
string (c : cs) = do
  char c
  string cs
  return (c : cs)

-- This parser recognises a nonempty sequence of terms separated by composition signs ‘.’.
expr :: Parser Expr
expr = do
  xs <- someWith (token (char '.')) term
  return (compose xs)

parseExpr :: String -> Expr
parseExpr = runParser expr

-- This parser recognises a variable or constant.
term :: Parser Expr
term = do
  space
  c <- letter
  cs <- many letter
  -- Note: variables are single-letter, constants are multi-letter
  if null cs
    then return (Var c)
    else Con (c : cs) <$> argument

-- Recognise an argument of a constant function
argument :: Parser [Expr]
argument = tuple <|> noTuple <|> return []
  where
    -- Parse single argument in e.g, f a -> [a]
    noTuple :: Parser [Expr]
    noTuple = do
      space
      c <- letter
      cs <- many letter
      if null cs
        then return [Var c]
        else return [Con (c : cs) []]
    -- Parse tuple arguments in e.g, f(a, b) -> [a, b]
    tuple :: Parser [Expr]
    tuple = do
      token (char '(')
      xs <- someWith (token (char ',')) expr
      token (char ')')
      return xs

