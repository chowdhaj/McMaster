\documentclass{article}
%include polycode.fmt
\begin{document}

{\Large \textbf{Comp Sci 3FP3 Midterm 2}}

\noindent
You are expected to use Haskell to do this test.
Code that does not compile will be worth no marks. If you
want to submit 'pseudocode', do it in comments -- you may
get partial marks then.

You can re-use any code that was done in class. You can
either import it (best) or copy-paste (then say where you got it).
Be precise with your imports - we will be using 
|OPTIONS_GHC -Wall| to compile things.

\noindent
You may use any function from the Haskell Prelude and any
Haskell feature you wish to answer the questions.

\noident
This test is ``open book'' in that you may refer to written
resources on the Internet (and textbooks). If you end up using 
any of them, give a link in a comment in what you hand in.

\noindent
\textbf{This remains an individual test - you may not ask for
help from anyone else, in any way shape or form, except for the
Midterm channel on the course Teams.}

\begin{code}
{-# OPTIONS_GHC -Wall #-}

module Midterm2_Sol where

\end{code}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\noindent
Q1 Add |Times n e| to the |RE| language of |Feb04.lhs|, to denote the
language that matches exactly $n$ repetitions of |e|, where $n\geq 1$ (and an
error otherwise), and $n$ of type |Int|.  Add a case to both
|toRecog| and |enumerate| for that.  To implement |enumerate|, first
implement two auxilliary functions that enumerates via
\begin{enumerate}
\item via transformation to the |RE| language,
\item directly (hint: |repeat|, |take| and a fold)
\end{enumerate}
Use either of these in |enumerate| itself.

ANSWER
\begin{code}
import Control.Monad.State
import Control.Applicative hiding ((<**>))
import Jan26 hiding ((<*>))

infixr 7 :|:
infixr 5 :*:

data RE =
    Eps
  | Ch Char
  | RE :|: RE
  | RE :*: RE 
  | St RE
  | Plus RE
  | Times Int RE
  deriving (Eq, Show)

toRecog :: RE -> RegExp
toRecog Eps = eps
toRecog (Ch c) = char c
toRecog (e1 :|: e2) = toRecog e1 ||| toRecog e2
toRecog (e1 :*: e2) = toRecog e1 <**> toRecog e2
toRecog (St e)      = star (toRecog e)
toRecog (Plus e)    = toRecog (e :*: St e)
toRecog (Times n e) 
  | n < 1 = error "must have a positive number of times"
  | n == 1 = toRecog e
  | otherwise = toRecog e <**> toRecog (Times (n-1) e)

interleave :: [a] -> [a] -> [a]
interleave [] ys = ys
interleave (x:xs) ys = x : interleave ys xs

cartesian :: [[a]] -> [[a]] -> [[a]]
cartesian []       _  = []
cartesian (x : xs) ys = [ x ++ y | y <- ys ] `interleave` cartesian xs ys

enumerate :: RE -> [ String ]
enumerate Eps         = [ "" ]
enumerate (Ch d)      = [ [d] ]
enumerate (e1 :|: e2) = enumerate e1 `interleave` enumerate e2
enumerate (e1 :*: e2) = enumerate e1 `cartesian` enumerate e2
enumerate (St e)      = result
  where -- Laziness FTW!
    result = [""] ++ (enumerate e `cartesian` result)
enumerate (Plus e)    = enumerate (e :*: St e)
enumerate (Times n e) = enumT2 n e

enumT1 , enumT2 :: Int -> RE -> [ String ]
enumT1 n e 
  | n < 1 = error "must have positive number of times"
  | n == 1 = enumerate e
  | otherwise = enumerate (e :*: Times (n-1) e)

enumT2 n e
  | n < 1 = error "must have positive number of times"
  | otherwise = foldl cartesian [""] (take n $ repeat (enumerate e))

ee :: RE
ee = (Ch 'a' :*: Ch 'b') :|: Ch 'c'
tst :: RE
tst = Times 3 ee
\end{code}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\noindent
Q2 This continues Q1.  Prove that
\begin{verbatim}
enumerate (Times 2 e) = enumerate (e :*: e)
\end{verbatim}
for all |e| in |RE|.  Hint: this proof does \emph{not} need
induction on RE, if you choose either the "correct" fold or a definition
of enumerate that makes things easy.
The result does hold for either choice of fold, but one choice does require
induction.

potentially useful lemmas:
\begin{verbatim}
l1 : xs `interleave` [] = xs
l2 : [ y | y <- xs ] = xs
\end{verbatim}

\noindent
ANSWER

enumerate (Times 2 e) == -- by definition enumT2
foldl cartesian [""] (take 2 (repeat (enumerate e))) == -- definition of take
foldl cartesian [""] [enumerate e, enumerate e] == -- definition of foldl
([""] `cartesian` enumerate e) `cartesian` enumerate e == -- definition of cartesian
([ "" ++ y | y <- enumerate e ] `interleave` (cartesian [] ys)) `cartesian` enumerate e ==
([ y | y <- enumerate e ] `interleave` []) `cartesian` (enumerate e) ==
enumerate e `cartesian` enumerate e ==
enumerate (e :*: e)
 
enumerate (Times 2 e) == -- by definition enumT1
enumerate (e :*: Times 1 e) ==
enumerate e `cartesian` enumerate (Times 1 e) ==
enumerate e `cartesian` enumerate e ==
enumerate (e :*: e)
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\noindent
Q3
\begin{code}
data Three a = Zero | One a | Two a a
\end{code}
\begin{enumerate}
\item Provide a |Functor| instance for |Three|.
\item Prove the fmap-id law for this |Functor|
\item Explain why there cannot be a Monad instance for |Three|
\end{enumerate}

\noindent
ANSWER
\begin{code}
instance Functor Three where
  fmap _ Zero = Zero
  fmap f (One a) = One $ f a
  fmap f (Two a b) = Two (f a) (f b)
\end{code}

There are 3 cases:
fmap id Zero = Zero = id Zero
fmap id (One a) = One (id a) = One a = id (One a)
fmap id (Two a b) = Two (id a) (id b) = Two a b = id (Two a b)

Because Two (Two x y) (Two z w) cannot be flattened.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\noindent
Q4
Start with RE from Feb04 and RegExp from Jan26, and the following code.
\begin{code}
newtype REW = REW {unR :: RegExp }
newtype S = S {unS :: [ String ] }
\end{code}
\begin{enumerate}
\item translate it to (untyped) tagless form. Call it |RESym|.
\item implement an instance of |RESym| for RE
\item implement an instance of |RESym| for |REW|
\item implement an instance of |RESym| for |S|, i.e. enumerate
\item answer: why the \emph{untyped} form?
\end{enumerate}

\noindent
ANSWER
\begin{code}
class RESym e where
  epsi :: e
  ch :: Char  -> e
  or_ :: e -> e -> e
  follow :: e -> e -> e
  st :: e -> e
  plus :: e -> e
  
instance RESym RE where
  epsi = Eps
  ch = Ch
  or_ = (:|:)
  follow = (:*:)
  st = St
  plus = Plus

instance RESym REW where
  epsi = REW eps
  ch = REW . char
  or_ = \x y -> REW ((unR x) ||| (unR y))
  follow = \x y -> REW ((unR x) <**> (unR y))
  st = REW . star . unR
  plus = \x -> REW ( (unR x) <**> star (unR x))

instance RESym S where
  epsi = S (enumerate Eps)
  ch = S . enumerate . Ch
  or_ = \x y -> S ((unS x) `interleave` (unS y))
  follow = \x y -> S ((unS x) `cartesian` (unS y))
  st = \x -> let result = [""] ++ ((unS x) `cartesian` result) in S result
  plus x = x `follow` (st x)
\end{code}

untyped because the various parts of the language are not about different
things, they are uniform. The type would be the same everywhere, so there
is no point adding noise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q5

Prove for the |[]| (list) instance of |Monad|, defining
\begin{verbatim}
  return x = [x , x]
\end{verbatim}
would violate at least one law.

Prove that for the |[]| (list) instance of |Functor|, defining
\begin{verbatim}
  fmap f x = []
\end{verbatim}
would violate at least one law.

ANSWER
rhs:
return x >>= f = --
[x , x ] >>= f =
concat [f x, f x]

lhs:
f x

%%
fmap id x =
[]
is not equal to
id x =
x

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q6
Consider the following definitions for a stateful language.
\begin{code}
data ThreeVars = TV { v1 :: Integer, v2 :: Integer, v3 :: Bool }

data I a = I {unI :: State ThreeVars a}

class IntSym rep where
  int     :: Integer -> rep Integer
  add     :: rep Integer -> rep Integer -> rep Integer
  sub     :: rep Integer -> rep Integer -> rep Integer

class BoolSym rep where
  bool    :: Bool -> rep Bool

class OrdSym rep where
  gt      :: rep Integer -> rep Integer -> rep Bool

class StatSym rep where
  seq_ :: rep a -> rep b -> rep b
  assign1 :: rep Integer -> rep Integer
  assign2 :: rep Integer -> rep Integer
  assign3 :: rep Bool    -> rep Bool   
  get1    :: rep Integer
  get2    :: rep Integer
  get3    :: rep Bool
  while   :: rep Bool -> rep a -> rep ()
  
prog :: (OrdSym rep, BoolSym rep, IntSym rep, StatSym rep) => rep Integer
prog = 
  assign1 (int 5)               `seq_`
  assign2 (int 17)              `seq_`
  assign3 (bool True)           `seq_`
  while (get3) (
    assign1 (sub get1 (int 1))  `seq_`
    assign2 (add get2 (int 1))  `seq_`
    assign3 (gt get1 (int 0)) ) `seq_`
  get2

run :: State ThreeVars a -> a
run x = fst $ runState x $ TV { v1 = 0, v2 = 0, v3 = False }

instance Functor I where
  fmap f (I s) = I (fmap f s)
instance Applicative I where
  pure = I . pure
  (I f) <*> (I x) = I $ f <*> x

instance Monad I where
  return = I . return
  (I a) >>= f = I $ do
     x <- a
     y <- unI $ f x
     return y

\end{code}
Implement an interpreter for that language, i.e. an instance for |I|.
This question is harder, you should save it for last.

|run (unI prog)| should return 22.

Hint: look up |Control.Monad.State|, especially |get|, |put|, and |modify|.
The \emph{do} notation is extremely helpful.

\noindent ANSWER
\begin{code}
instance IntSym I where
  int = pure
  add = liftA2 (+)
  sub = liftA2 (-)

instance BoolSym I where
  bool = pure

instance OrdSym I where
  gt   = liftA2 (>)

instance StatSym I where
  seq_ a b = do { _ <- a ; b }
  assign1 (I i) = I $ do
    j <- i
    s <- get
    put (s { v1 = j })
    return j
  assign2 (I i) = I $ do
    j <- i
    s <- get
    put (s { v2 = j })
    return j
  assign3 (I i) = I $ do
    j <- i
    s <- get
    put (s { v3 = j })
    return j
  get1 = I $ do
    s <- get
    return $ v1 s
  get2 = I $ do
    s <- get
    return $ v2 s
  get3 = I $ do
    s <- get
    return $ v3 s
  while (I bl) (I body) = I $ do
    b <- bl
    if b then
      do
        _ <- body
        unI $ while (I bl) (I body)
    else
      return ()

\end{code}

\end{document}
