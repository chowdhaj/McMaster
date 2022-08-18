{-# LANGUAGE InstanceSigs #-}
module Parser where

import Data.Char (digitToInt, isAlpha, isDigit, isSpace)
import Data.List (partition)

todo :: String -> a
todo e = error (e ++ " is not yet implemented!")

-------------------------------------------------------------------------------
-- In A3 this was ‘parse’, now ‘applyParser’.
newtype Parser a = MkP {applyParser :: String -> Parsed a}

data Parsed a
  = Failure
  | Success {value :: a, remainingInput :: String}
  deriving (Show, Eq, Ord)

instance Functor Parsed where
  fmap f Failure = Failure
  fmap f (Success v rest) = Success (f v) rest

instance Functor Parser where
  fmap f p = MkP $ fmap f . applyParser p

instance Applicative Parser where

  -- `pure` - This is `success` in our assignment
  pure :: a -> Parser a
  pure x = MkP $ Success x

  funP <*> aP = MkP $ \input -> case applyParser funP input of
    Failure -> Failure
    Success f rem -> f <$> applyParser aP rem

instance Monad Parser where

  -- `return` - This is `success` in our assignment
  return = pure

  -- `bind` - This is `andThen` in our assignment
  (>>=) :: Parser a -> (a -> Parser b) -> Parser b
  p >>= f = MkP $ \input -> case applyParser p input of
    Failure -> Failure
    Success a rem -> applyParser (f a) rem

-- Get value result from applying a parser.
runParser :: Parser a -> String -> a
runParser p inp = case applyParser p inp of
  Failure -> error "Parser failed!"
  Success a rem -> a

-- Parser that always fails.
failure :: Parser a
failure = MkP $ const Failure

-- Parse the first character of the input if it's non empty, otherwise fails
item :: Parser Char
item = MkP $ \inp -> case inp of
  [] -> Failure
  (c : cs) -> Success c cs

-- Parse a character satisfying predicate p
sat :: (Char -> Bool) -> Parser Char
sat p = do
  c <- item
  if p c
    then return c
    else failure

-- Look for a specific character as the next item in the input string
char :: Char -> Parser Char
char c = sat (== c)

-- Look for a digit, returning the associated numeric value if successful
digit :: Parser Int
digit = do
  d <- sat isDigit
  return $ digitToInt d

-- orElse (hoogle "Alternative")
(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = MkP $ \input -> case applyParser p input of
  Failure -> applyParser q input
  Success a rem -> Success a rem

many :: Parser a -> Parser [a]
many p = get <|> pure []
  where
    get = do
      x <- p
      xs <- many p
      return (x : xs)

-- Parse a list of something with given separator (requires at least one)
someWith :: Parser s -> Parser a -> Parser [a]
someWith separator p = do
  x <- p
  xs <- many (do separator; p)
  return (x : xs)
