{-# OPTIONS_GHC -Wall #-}

module A1_solution where

import Prelude hiding (reverse, all)

{-
  Preface: 4 marks
  Q1:      9 marks
  Q2:      2 marks
  Q3:      6 marks
  Q4:      8 marks
  Q5:      6 marks
  Q6:      8 marks
  Q7:      5 marks
  Q8:      5 marks
  Q9:      14 marks
  Q10:     20 marks

  Total:   87 marks
-}



{------------------------------------------------------
-----                  PREFACE                    -----
-------------------------------------------------------
----- Well structured document (2 marks)
----- Well named document + "module" header (2 marks)
----- 
----- TOTAL: 4 marks
-------------------------------------------------------}



{------------------------------------------------------
-----                    Q1                       -----
-------------------------------------------------------
----- 3 functions
-----   * matches: 2 marks
-----   * element: 2 marks
-----   * pos:     3 marks
----- 1 question (2 marks [answer + justification])
----- 
----- TOTAL: 9 marks
-------------------------------------------------------}

matches :: Eq a => a -> [a] -> [a]
matches _ [] = []
matches a (x:xs)
  | x == a    = x : matches a xs
  | otherwise = matches a xs

element :: Eq a => a -> [a] -> Bool
element _ []     = False
element a (x:xs) = x == a || element a xs

pos :: Eq a => a -> [a] -> [Integer]
pos _ [] = []
pos a (x:xs)
  | x == a    = 0 : map (+1) (pos a xs)
  | otherwise = map (+1) (pos a xs)

-- "pos" gives the most information, it's the best, can also be used to derive the others
-- "element" might be the best if you don't care about "where/when" occurrences exist
-- "matches" provides nearly no information about the occurrences

{------------------------------------------------------
-----                    Q2                       -----
-------------------------------------------------------
----- 1 function (2 marks)
----- 
----- TOTAL: 2 marks
-------------------------------------------------------}

applyAll :: [a -> b] -> [a] -> [b]
applyAll []     _  = []
applyAll (f:fs) as = map f as ++ applyAll fs as

{------------------------------------------------------
-----                    Q3                       -----
-------------------------------------------------------
----- 2 function
-----   * tripleNeg1: 2 marks
-----   * tripleNeg2: 4 marks
----- 
----- TOTAL: 6 marks 
-------------------------------------------------------}

tripleNeg1 :: (Ord a, Num a) => [a] -> [a]
tripleNeg1 [] = []
tripleNeg1 (x:xs)
  | x < 0     = (x * 3) : tripleNeg1 xs
  | otherwise = x : tripleNeg1 xs

tripleNeg2 :: (Ord a, Num a) => [a] -> [a]
tripleNeg2 = map (either (*3) id . (\x -> if x < 0 then Left x else Right x))

{------------------------------------------------------
-----                    Q4                       -----
-------------------------------------------------------
----- 2 functions (3 marks each)
----- 1 question (2 marks [answer + justification])
----- 
----- TOTAL: 8 marks
-------------------------------------------------------}

data OrBoth a b = JustLeft a | JustRight b | Both a b

consume1 :: (a -> c) -> (b -> c) -> (a -> b -> c) -> OrBoth a b -> c
consume1 f _ _ (JustLeft a)  = f a
consume1 _ g _ (JustRight b) = g b
consume1 _ _ h (Both a b)    = h a b

consume2 :: (a -> c) -> (b -> c) -> (c -> c -> c) -> OrBoth a b -> c
consume2 f _ _ (JustLeft a)  = f a
consume2 _ g _ (JustRight b) = g b
consume2 f g h (Both a b)    = h (f a) (g b)

-- consume1 is better because the third function is not contrained to
-- be using first 2 functions. If we directly need to use the values in
-- the third function, then it becomes a bit difficult in many cases.

{------------------------------------------------------
-----                    Q5                       -----
-------------------------------------------------------
----- 2 functions (3 marks each)
----- 
----- TOTAL: 6 marks
-------------------------------------------------------}

data Ternary a = TLeaf a | TNode (Ternary a) (Ternary a) (Ternary a)

mirror :: Ternary a -> Ternary a
mirror (TLeaf a)     = TLeaf a
mirror (TNode a b c) = TNode (mirror c) (mirror b) (mirror a)

flattenTernary :: Ternary a -> [a]
flattenTernary (TLeaf a)     = [a]
flattenTernary (TNode a b c) = flattenTernary a ++ flattenTernary b ++ flattenTernary c

{------------------------------------------------------
-----                    Q6                       -----
-------------------------------------------------------
----- 1 induction proof
-----   * base case = 2 marks
-----   * induction step = 2 marks
-----   * stating induction hypothesis = 1 mark
-----   * conclusive statements = 2 marks
-----   * well named and existant properties = 1 mark
----- 
----- TOTAL: 8 marks
-------------------------------------------------------}

all :: (a -> Bool) -> [a] -> Bool
all _ []     = True            -- all.1
all p (x:xs) = p x && all p xs -- all.2

{-

all p (xs ++ ys) = all p xs && all p ys

Proof by induction on xs

Base case xs = []

LHS:
  all p ([] ++ ys)
={ Identity of ++ }
  all p ys

RHS:
  all p [] && all p ys
={ all.1 }
  True && all p ys
={ Identity of && }
  all p ys

Therefore, LHS = RHS, and the base case holds!


Induction step! (x:xs)
e.g., CHECK: all p ((x:xs) ++ ys) = all p (x:xs) && all p ys

We assume the property holds for xs!
e.g., `all p (xs ++ ys) = all p xs && all p ys`

  all p ((x:xs) ++ ys)
={ ++.2 }
  all p (x:(xs ++ ys))
={ all.2 }
  p x && all p (xs ++ ys)
={ ind. hyp. }
  p x && (all p xs && all p ys)
={ associativity of && }
  (p x && all p xs) && all p ys
={ all.2 }
  all p (x:xs) && all p ys

Therefore, LHS = RHS, and the induction step holds!

Therefore, this property holds.

-}

{------------------------------------------------------
-----                    Q7                       -----
-------------------------------------------------------
----- 1 function (3 marks)
----- 1 type analysis (1 mark)  -- getting _any_ workable type signature
----- 1 correct "least constraining type" (1 mark)
----- 
----- TOTAL: 5 marks
-------------------------------------------------------}

mystery :: ((a, b) -> c) -> [a] -> [b] -> [c]
mystery f (x:xs) (y:ys) = f (x, y) : mystery f xs ys
mystery _ _ _           = []

{------------------------------------------------------
-----                    Q8                       -----
-------------------------------------------------------
----- 1 function (4 marks)
----- 1 implicit type signature (1 mark)
----- 
----- TOTAL: 5 marks
-------------------------------------------------------}

reverse :: [a] -> [a]
reverse = foldr (\x xs -> xs ++ [x]) []

{------------------------------------------------------
-----                    Q9                       -----
-------------------------------------------------------
----- 2 functions (3 marks each)
----- 1 induction proof
-----   * base case = 2 marks
-----   * induction step = 2 marks
-----   * stating induction hypothesis = 1 mark
-----   * conclusive statements = 2 marks
-----   * well named and existant properties = 1 mark
----- 
----- TOTAL: 14 marks
-------------------------------------------------------}

data Tree a = Tip | Node (Tree a) a (Tree a) deriving (Show, Eq)

mirrorTree :: Tree a -> Tree a
mirrorTree Tip          = Tip                                   -- mirror.1
mirrorTree (Node l a r) = Node (mirrorTree r) a (mirrorTree l)  -- mirror.2


pre :: Tree a -> [a]
pre Tip          = []                       -- pre.1
pre (Node l a r) = a : pre l ++ pre r       -- pre.2

post :: Tree a -> [a]
post Tip          = []                      -- post.1
post (Node l a r) = post l ++ post r ++ [a] -- post.2

{-
Property = pre (mirrorTree t) = reverse (post t)

Proof by induction on tree t, using standard library reverse, marked with reverse.1 and reverse.2

Base case!    t = Tip:

LHS:
  pre (mirrorTree Tip)
={ mirror.1 }
  pre (Tip)
={ pre.1 }
  []

RHS:
  reverse (post Tip)
={ post.1 }
  reverse []
={ reverse.1 }
  []

Therefore, LHS = RHS, and base case holds!


Induction step!   t = Node l a r
Induction hypothesis: pre (mirrorTree l) = reverse (post l)
                  AND pre (mirrorTree r) = reverse (post r)

LHS:
  pre (mirrorTree (Node l a r))
={ mirrorTree.2 }
  pre (Node (mirrorTree r) a (mirrorTree l))
={ pre.2 }
  a : pre (mirrorTree r) ++ pre (mirrorTree l)
={ ind. hyp. }
  a : reverse (post r) ++ reverse (post l)
={ inversion of reverse }
  reverse (reverse (a : reverse (post r) ++ reverse (post l)))
={ reverse.2 }
  reverse (reverse (reverse (post r) ++ reverse (post l)) ++ [a])
={ reverse }
  reverse (reverse (reverse (post l)) ++ reverse (reverse (post r)) ++ [a])
={ inversion of reverse }
  reverse (post l ++ post r ++ [a])

RHS:
  reverse (post (Node l a r))
={ post.2 }
  reverse (post l ++ post r ++ [a])

Therefore, LHS = RHS, and induction step holds!

Therefore, this property holds.

-}

{------------------------------------------------------
-----                    Q10                      -----
-------------------------------------------------------
----- 4 functions (4 marks each)
----- 2 isomorphism properties between functions upheld (2 marks each)
----- 
----- TOTAL: 20 marks
-------------------------------------------------------}

-- From W2020 solution by Nhan Thai and Habib Ghaffari

data Rose a = Rose a [Rose a] deriving (Show, Eq)
data Fork a = Leaf a | Branch (Fork a) (Fork a) deriving (Show, Eq)

to' :: Tree a -> [Rose a]
to' Tip = []
to' (Node l a r) = rose : roses
  where
    subRoses = to' l
    roses = to' r
    rose = Rose a subRoses

from' :: [Rose a] -> Tree a
from' [] = Tip
from' (rose : roses) = Node l a r
  where
    Rose a subRoses = rose
    l = from' subRoses
    r = from' roses

to :: Rose a -> Fork a
to (Rose a []) = Leaf a
to (Rose a (rose : subRoses)) = Branch l r
  where
    l = to rose
    r = to (Rose a subRoses)

from :: Fork a -> Rose a
from (Leaf a) = Rose a []
from (Branch l r) = Rose a (rose : subRoses)
  where
    rose = from l
    Rose a subRoses = from r

