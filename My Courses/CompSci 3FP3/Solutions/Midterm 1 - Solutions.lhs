\documentclass{article}
%include polycode.fmt
\begin{document}

{\Large \textbf{Comp Sci 3FP3 Midterm 1}}

\noindent
You are expected to use Haskell to do this assignment.
Code that does not compile will be worth no marks. If you
want to submit 'pseudocode', do it in comments -- you may
get partial marks then.

\noindent
You may use any function from the Haskell Prelude and any
Haskell feature you wish to answer the questions. Useful
definitions can be found at the end.

\begin{code}
module Midterm1_Solution where

-- see at end
import Prelude hiding (maximum, minimum, length, map, zip)
\end{code}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\noindent
Q1 (4 marks)

Breakdown:
  * q1: 2 marks (answer + explanation)
  * q2: 2 marks (answer + explanation)

\noindent
The |zip| function
\begin{code}
zip :: [a] -> [b] -> [(a,b)]
zip (x:xs) (y:ys) = (x,y) : zip xs ys       -- zip.1
zip _ _ = []                                -- zip.2
\end{code}
\noindent
\emph{loses information}. 
\begin{enumerate}
  \item Figure out what \emph{loses information} means from the definition
       above, and explain what it means in the context of |zip|.
  \item There is however an explicit mathematical invariant that holds between
       the length of the input lists and the result of |zip|. Find and
        write out this invariant.
\end{enumerate}

\textbf{Answer}:

\begin{enumerate}
    \item "loses information" means that it does not return the same amount of data that was inputted. It ignores/removes/"loses" some of the inputted information. In this case, when the length of the first 2 lists are not the same, the values leftover of the longer list are "lost".
    \item @length (zip a b) = min (length a, length b)@
\end{enumerate}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q2 (6 marks)

Breakdown:
  * meld function: 3 marks
  * invariant: 1 mark
  * question: 2 marks (answer + explanation)

\noindent
Consider the following definitions:
\begin{code}
data LeftLeaning a  = LNil | LCons (LeftLeaning a) a
data RightLeaning a = RNil | RCons a (RightLeaning a)

meld :: (a -> b -> c) -> a -> b -> LeftLeaning a -> RightLeaning b -> [c]
meld f ia ib (LCons l vl) (RCons vr r) = f vl vr : meld f ia ib l r
meld f ia ib LNil (RCons vr r) = f ia vr : meld f ia ib LNil r
meld f ia ib (LCons l vl) RNil = f vl ib : meld f ia ib l RNil
meld _ _ _ _ _ = []

\end{code}
\noindent Implement |meld|.  Every argument of |meld| must be used in
at least one case of the implementation. \textbf{All the elements} in 
the inputs of type |LeftLeaning a| and |RightLeaning b|
must be used.



\noindent
For this function, like for the previous one, there is an explicit
invariant that holds between
the inputs of type |LeftLeaning a| and
|RightLeaning b| and the length of the output. What is it?

|meld| is a variation of a function that is in the Haskell
Prelude.  Which one, and explain why.

\textbf{Answer}:

Invariant:
@length (meld f ia ib l r) = max ("length" l) ("length" r)@ -- assuming we can use some other "length" on LeftLeaning and RightLeaning as well

|meld| is a variation of zipWith. They have very similar type signatures but meld fully merges with fallback/default values, losing no information.

By extension, it can be thought of as a variation of zip on LeftLeaning and RightLeaning constructions that does as discussed above.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q3 {2 marks}

Breakdown:
  * q3 function: 2 marks

\noindent
Write a function that given a list of lists returns
only the lists of 3 or more elements. Ensure you maintain the list order.
Also make sure your function works even when ``inner'' lists
are infinite, such as |[[12,13],[1,2,3],[4..],[-4..],[1],[0]]|,
where the result would be |[[1,2,3],[4..],[-4..]]|.
A simpler example: Given |[[1,2,3],[4,5],[6,7,8,9]]| 
\emph{the result should be} |[[1,2,3],[6,7,8,9]]|.

\begin{code}

q3 :: [[a]] -> [[a]]
q3 ((q@(a:b:c:ds)):xs) = q : q3 xs
q3 (_:xs) = q3 xs
q3 [] = []

\end{code}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q4 (6 marks)

Breakdown:
  * Base case: 2 marks
  * Induction step: 2 marks
  * question: 2 marks


\noindent
Prove that the following property always holds. 
\begin{code}
swap :: (a,b) -> (b,a)
swap (a,b) = (b,a)               -- swap.1

prop_midterm :: Eq a => Integer -> [a] -> Bool
prop_midterm n xs = zip [n..] xs == map swap (zip xs [n..])
\end{code}
\noindent Hint: Induction on the list.

\textbf{ANSWER}:

Induction!
Base case: xs = []

      zip [n...] []
    = []                                        -- zip.2
    = map swap []                               -- map.1
    = map swap (zip [] [n..])                   -- zip.2

Induction step: xs = y:ys

      map swap (zip (y:ys) [n..])
    = map swap ((y, n) : zip ys [(n+1)..])      -- zip.1
    = (n, y) : (map swap (zip ys [(n+1)..]))    -- map & swap
    = (n, y) : zip [(n+1)..] ys                 -- Induction hypothesis
    = zip [n..] (y:ys)                          -- zip.1


\noindent
Does your proof mean that this property holds for infinite list too?
(Explain your answer, this is not a yes/no question).

\textbf{ANSWER}:

Yes. If we have infinite lists, then we can just take as many values as we'd like out from the 
"head" of either list and they will be the same value, no matter what, thanks to induction and Haskell's laziness.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Q5 (5 marks)

Breakdown:
  * depth: 1.5 marks
  * nodes: 1.5 marks
  * maxBranch: 2 marks

\noindent
Here is the definition of a |Rose| tree:
\begin{code}
data Rose a = Rose a [Rose a]
\end{code}

\noindent
Write a function to compute the \emph{depth}
of a tree. |Rose 110 []| should have depth 0,
and |Rose 5 [Rose 3 [Rose 17 []]]| should have depth 2.

\begin{code}
depth :: Rose a -> Int
depth (Rose _ []) = 0
depth (Rose _ rs) = 1 + maximum (map depth rs)

\end{code}

\noindent
Write a function to compute the number of nodes (i.e. number of occurrences of
the constructor |Rose|) in your tree?

\begin{code}
nodes :: Rose a -> Int
nodes (Rose _ rs) = 1 + sum (map nodes rs)

\end{code}

\noindent
Write a function to compute the maximal branching, i.e. the size of the largest
list contained in the tree?

\begin{code}
maxbranch :: Rose a -> Int
maxbranch (Rose _ rs) = maximum $ length rs : map maxbranch rs

\end{code}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\begin{code}
maximum :: Ord a => [a] -> a
maximum [] = error "maximum of empty list does not exist"
maximum [x] = x
maximum (x:xs) = max x (maximum xs)

minimum :: Ord a => [a] -> a
minimum [] = error "minimum of empty list does not exist"
minimum [x] = x
minimum (x:xs) = min x (minimum xs)

length :: [a] -> Int
length []     = 0                  -- len.1
length (_:xs) = 1 + length xs      -- len.2

map :: (a -> b) -> [a] -> [b]
map _ [] = []                      -- map.1
map f (x : xs) = f x : map f xs    -- map.2
\end{code}
\end{document}