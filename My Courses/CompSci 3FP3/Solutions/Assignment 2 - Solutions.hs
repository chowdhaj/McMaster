{-# OPTIONS_GHC -Wall #-}

module A2Solution where

{-

Marks:
    Preface: /4
    Q1: /8
    Q2: /8
    Q3: /8
    Q4: /8
    Q5: /3
    Q6: /12
    Q7: /11
    Q8: /3
    Q9: /18

    TOTAL: /83

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
----- 1 induction proof
-----   * base case = 2 marks
-----   * induction step = 2 marks
-----   * stating induction hypothesis = 1 mark
-----   * conclusive statements = 2 marks
-----   * well named and existant properties = 1 mark
----- 
----- TOTAL: 8 marks
-------------------------------------------------------}

{-

Proof: iter n id = id

Let's prove this with induction!

Base case: n = 0
----------------

LHS:
    iter 0 id
={ iter.2 }
    id
RHS:

Therefore, our base case holds.

Induction step: n = k + 1
-------------------------
First, let us recall our induction hypothesis:
    iter k id = id

Now, we will prove that our induction step holds for n = k + 1

LHS:
    iter (k + 1) id
={ iter.1 }
    id . iter ((k + 1) - 1) id
={ evaluation }
    id . iter k id
={ ind. hyp. }
    id . id
={ identity of id }
    id
RHS:

Therefore, our induction step.

Finally, we have shown that both our induction step and our 
base case holds, and therefore we have proven through induction
that this property holds for all natural numbers, n.

Q.E.D.

-}


{------------------------------------------------------
-----                    Q2                       -----
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


{-


Proof: map f (ys ++ zs) = map f ys ++ map f zs
    (forall ys, zs : [a], f : a -> b)

Let's prove this with induction!

Base case: ys = []
------------------

LHS:
    map f ([] ++ zs)
={ ++.1 }
    map f zs
={ ++.1 }
    []  ++ map f zs
={ empty mapping (map.1) }
    map f [] ++ map f zs
RHS:

Therefore we have shown LHS = RHS and hence the base case holds.


Induction step: ys = x:xs
-------------------------
We shall first note our induction hypothesis:
    map f (xs ++ zs) = map f xs ++ map f zs


LHS:
    map f ((x:xs) ++ zs)
={ ++.2 }
    map f (x:(xs ++ zs))
={ map.2 }
    (f x):map f (xs ++ zs)
={ ind. hyp. }
    (f x):(map f xs ++ map f zs)
={ ++.2 }
    ((f x):map f xs) ++ map f zs
={ map.2 }
    map f (x:xs) ++ map f zs
RHS:

Therefore, our LHS = RHS, and our induction case holds!


Therefore, we have shown that both our base case and our
induction step holds, and, as such, we have also shown
through induction that this property holds for all list
constructions.

Q.E.D.

-}


{------------------------------------------------------
-----                    Q3                       -----
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


{-


Proof: concat (map (map f) xs) = map f (concat xs)

where
concat :: [[a]] -> [a]
concat = foldr (++) []      -- concat.1

We shall recall our foldr function:
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f s []     = s                          -- foldr.1
foldr f s (x:xs) = x `f` (foldr f s xs)       -- foldr.2


Let's use induction!

Base case: xs = []
------------------

LHS:
    concat (map (map f) [])
={ map.1 }
    concat []
={ concat.1 }
    foldr (++) [] []
={ foldr.1 }
    []
={ map.1 }
    map f []
={ foldr.1 }
    map f (foldr (++) [] [])
={ concat.1 }
    map f (concat [])
RHS:

Therefore, our LHS = RHS, and hence our base case holds.

Induction step: xs = y:ys
-------------------------

First, we shall note our induction hypothesis:
    concat (map (map f) ys) = map f (concat ys)

Now, let us observe xs:

LHS:
    concat (map (map f) (y:ys))
={ map.2 }
    concat ((map f y):(map (map f) ys))
={ concat.2 }
    foldr (++) [] ((map f y):(map (map f) ys))
={ foldr.2 }
    map f y ++ foldr (++) [] (map (map f) ys)
={ concat.2 }
    map f y ++ concat (map (map f) ys)
={ ind. hyp. }
    map f y ++ map f (concat ys)
={ Q2 Proof }
    map f (y ++ concat ys)
={ concat.1 }
    map f (y ++ foldr (++) [] ys))
={ foldr.2 }
    map f (foldr (++) [] (y:ys))
={ concat.2 }
    map f (concat (y:ys))
RHS:

Therefore, our LHS = RHS, and hence we know that our
induction step holds!


Finally, we have shown that our base case and our
induction step, and, as such, we have shown through
induction that this property holds.

Q.E.D.

-}

{------------------------------------------------------
-----                    Q4                       -----
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


{-


filter p (filter q xs) = filter (p &&& q) xs

where
p &&& q = \x -> p x && q x

We should note some things first:
    p, q :: a -> Bool
    (&&&) :: (a -> Bool) -> (a -> Bool) -> a -> Bool

-- with filter from https://hackage.haskell.org/package/base-4.14.1.0/docs/src/GHC.List.html#filter
filter :: (a -> Bool) -> [a] -> [a]
filter _pred []    = []                            -- filter.1
filter pred (x:xs)                                 -- filter.2
  | pred x         = x : filter pred xs
  | otherwise      = filter pred xs


For the sake of rewriting it filter into another form, we shall use the following rewrite:
filter pred (x:xs) = if pred x then x : filter pred xs
                               else filter pred xs


Finally, via induction on xs, we will prove this:

Proof: filter p (filter q xs) = filter (p &&& q) xs
    (forall p, q :: a -> Bool, xs :: [a])

Base case: xs = []
------------------

LHS:
    filter p (filter q [])
={ filter.1 }
    filter p []
={ filter.1 }
    []
={ filter.1 }
    filter (p &&& q) []
RHS:

Therefore, our base case holds (since LHS = RHS).

Induction step: xs = y:ys
-------------------------
First, we shall note our induction hypothesis:
    filter p (filter q ys) = filter (p &&& q) ys

LHS:
    filter p (filter q (y:ys))
={ filter.2 }
    filter p (
                 if q y then y:(filter q ys)
                        else filter q ys
             )
={ filter.2 }
    if p y && q y then y:(filter p (filter q ys))
                  else filter p (filter q ys)
={ rewrite using lambda }
    if (\x -> p x && q x) y then y:(filter p (filter q ys))
                            else filter p (filter q ys)
={ def. of &&& }
    if (p &&& q) y then y:(filter p (filter q ys))
                   else filter p (filter q ys)
={ ind. hyp. }
    if (p &&& q) y then y:(filter (p &&& q) ys)
                   else filter (p &&& q) ys
={ filter.2 }
    filter (p &&& q) (y:ys)
RHS:

Therefore, LHS = RHS, and hence our induction step holds.

Therefore, we have shown that both our base case holds and
our induction step holds. Therefore, we have shown through
induction that this property holds.

Q.E.D.

-}



{------------------------------------------------------
-----                    Q5                       -----
-------------------------------------------------------
----- 1 function (3 marks)
----- 
----- TOTAL: 3 marks
-------------------------------------------------------}


data Expr = Lit Integer | Expr :+: Expr | Expr :-: Expr

size :: Expr -> Integer
size (Lit _)   = 0
size (a :+: b) = 1 + size a + size b
size (a :-: b) = 1 + size a + size b


{------------------------------------------------------
-----                    Q6                       -----
-------------------------------------------------------
----- 2 data type change (1 mark each)
----- 3 functions (3 marks each)
----- 1 question (1 mark)
----- 
----- TOTAL: 12 marks
-------------------------------------------------------}

data Expr' = Lit' Integer
           | Add' Expr' Expr'
           | Minus' Expr' Expr'
           | Mult' Expr' Expr'
           | Div' Expr' Expr'

-- Question Response:
--   When performing division by zero, we get a "division by zero" error.

show' :: Expr' -> String
show' (Lit' a) | a < 0     = "Lit' (" ++ show a ++ ")"
               | otherwise = "Lit' " ++ show a
show' (Add' a b)   = "Add' (" ++ show' a ++ ") (" ++ show' b ++ ")"
show' (Minus' a b) = "Minus' (" ++ show' a ++ ") (" ++ show' b ++ ")"
show' (Mult' a b)  = "Mult' (" ++ show' a ++ ") (" ++ show' b ++ ")"
show' (Div' a b)   = "Div' (" ++ show' a ++ ") (" ++ show' b ++ ")"

size' :: Expr' -> Integer
size' (Lit' _)     = 0
size' (Add' a b)   = 1 + size' a + size' b
size' (Minus' a b) = 1 + size' a + size' b
size' (Mult' a b)  = 1 + size' a + size' b
size' (Div' a b)   = 1 + size' a + size' b

eval' :: Expr' -> Integer
eval' (Lit' a)     = a
eval' (Add' a b)   = eval' a + eval' b
eval' (Minus' a b) = eval' a - eval' b
eval' (Mult' a b)  = eval' a * eval' b
eval' (Div' a b)   = eval' a `div` eval' b


{------------------------------------------------------
-----                    Q7                       -----
-------------------------------------------------------
----- 3 functions (3 marks each)
----- 1 question (2 marks)
----- 
----- TOTAL: 17 marks
-------------------------------------------------------}

data Expr2 =  Lit2 Integer
           | Op Ops Expr2 Expr2
    deriving Show

data Ops = Add | Sub | Mul | Div
    deriving Show

-- Question Response:
--   We would need to add an extra "Ops" constructor,
--   and then fill in the details to make all of the *Op
--   functions total (e.g., fill in showOp, evalOp)

show2Op :: Ops -> String 
show2Op Add = "Add"
show2Op Sub = "Sub"
show2Op Mul = "Mul"
show2Op Div = "Div"

eval2Op :: Ops -> (Integer -> Integer -> Integer)
eval2Op Add = (+)
eval2Op Sub = (-)
eval2Op Mul = (*)
eval2Op Div = div

show2 :: Expr2 -> String
show2 (Lit2 a) | a < 0     = "Lit2 (" ++ show a ++ ")"
               | otherwise = "Lit2 " ++ show a
show2 (Op o a b) = "Op " ++ show2Op o ++ " (" ++ show2 a ++ ") (" ++ show2 b ++ ")"

eval2 :: Expr2 -> Integer
eval2 (Lit2 a)   = a
eval2 (Op o a b) = eval2Op o (eval2 a) (eval2 b)

size2 :: Expr2 -> Integer
size2 (Lit2 _)   = 0
size2 (Op _ a b) = 1 + size2 a + size2 b


{------------------------------------------------------
-----                    Q8                       -----
-------------------------------------------------------
----- 1 function (3 marks)
----- 
----- TOTAL: 3 marks
-------------------------------------------------------}

join :: (a -> c) -> (b -> d) -> Either a b -> Either c d
join f g = either (Left . f) (Right . g)


{------------------------------------------------------
-----                    Q9                       -----
-------------------------------------------------------
----- 6 function (3 marks each)
----- 
----- TOTAL: 16 marks
-------------------------------------------------------}

data GTree a = Leaf a | Gnode [GTree a]
    deriving Show

count :: GTree a -> Integer
count (Leaf _)   = 1
count (Gnode ns) = sum (map count ns)

depth :: GTree a -> Integer
depth (Leaf _)   = 0
depth (Gnode []) = 0
depth (Gnode ns) = 1 + maximum (map depth ns)

sumTree :: GTree Int -> Int
sumTree (Leaf a)   = a
sumTree (Gnode ns) = sum (map sumTree ns)

elemTree :: Eq a => a -> GTree a -> Bool
elemTree v (Leaf a)   = v == a
elemTree v (Gnode ns) = any (elemTree v) ns

mapTree :: (a -> b) -> GTree a -> GTree b
mapTree f (Leaf a)   = Leaf (f a)
mapTree f (Gnode ns) = Gnode $ map (mapTree f) ns

flattenTree :: GTree a -> [a]
flattenTree (Leaf a)   = [a]
flattenTree (Gnode ns) = concatMap flattenTree ns
