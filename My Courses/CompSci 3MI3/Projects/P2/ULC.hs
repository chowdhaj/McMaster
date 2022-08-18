{-
AUTHOR  :: Jatin Chowdhary
MACID   :: Chowdhaj
COURSE  :: CompSci 3MI3
DATE    :: November 2nd, 2021
LICENSE :: GPL
-}

import Data.List

-- I had to define a main function, otherwise it wouldn't compile
-- Please delete if it bothers you or if it is not necessary
main :: IO ()
main = return ()

-------------------------------------------------
-- PART 1: IMPLEMENTED UNTYPED LAMBDA CALCULUS --
-------------------------------------------------

{--------------}
{- Question 1 -}
{--------------}

-- Var data type
data Var = A | B | C | D | E | F | G | H | I | J | K | M |
           N | O | P | Q | R | S | T | U | V | W | X | Y |
           Z
    deriving (Show, Eq)

-- Term data type
data Term = Label Var
          | Lambda (Var) (Term)
          | Apply (Term) (Term)
    deriving (Show, Eq)

{--------------}
{- Question 2 -}
{--------------}

freeVariable :: Term -> [Var]
freeVariable (Label var)         = [var]
freeVariable (Lambda var term)   = freeVariable term \\ [var]
freeVariable (Apply term1 term2) = unionVar
    where unionVar = union (freeVariable term1) (freeVariable term2)
--freeVariable _ = error "Invalid Term"

-- Note: 'var'  is basically 'x'
--       'term' is basically 't1'
-- I decided to stick to my naming convention, rather than variable
-- names in the definition provided; this was done for clarity

-- Initially, I used `nub` instead of `union`. The code is:
-- freeVariable (Apply term1 term2) =
--     nub ((freeVariable term1) ++ (freeVariable term2))
-- However, I switched to `union`, because I thought I would lose
-- marks for using `nub`. I prefer `nub` b/c it's funny. Haha!

-- Code used from Hoogle:
-- "dog" `union` "cow" -> "dogcw"
-- union "dog" "cow" -> "dogcw"
-- Note: `union` is an infix and prefix operator
-- "Hello World!" \\ "ell W" -> "Hoorld!"

{--------------}
{- Question 3 -}
{--------------}

reLabel :: Term -> Var -> Var -> Term
reLabel (Label currentVar) oldVar newVar =
    if (currentVar == oldVar)
        then (Label newVar)
            else (Label currentVar)
reLabel (Lambda currentVar term) oldVar newVar =
    if (currentVar == oldVar)
        then (Lambda newVar recursiveRelabel)
            else (Lambda currentVar recursiveRelabel)
    where recursiveRelabel = (reLabel term oldVar newVar)
reLabel (Apply term1 term2) oldVar newVar =
    Apply (reLabel term1 oldVar newVar)
          (reLabel term2 oldVar newVar)
--reLabel _ _ _ = error "Could Not Perform Relabeling"

{--------------}
{- Question 4 -}
{--------------}

sub :: Term -> Var -> Term -> Term
sub (Label currentVar) subVar term =
    if (currentVar == subVar) then term else (Label currentVar)
sub (Apply term1 term2) subVar term3 =
    Apply substituteTerm1 substituteTerm2
        where substituteTerm1 = (sub term1 subVar term3)
              substituteTerm2 = (sub term2 subVar term3)
sub (Lambda currentVar term1) subVar term2 =
    if (currentVar == subVar) then (Lambda currentVar term1) else
        if isVarInFree then substituteUnused else substituteTerm
            where isVarInFree = currentVar `isAnElementOf` (freeVariable term2)
                  substituteUnused = (Lambda freeVar (sub replaceTerm subVar term2))
                        where freeVar = (getFirstFreeVariable (freeVariable term2))
                              replaceTerm = (reLabel term1 currentVar freeVar)
                  substituteTerm = (Lambda currentVar (sub term1 subVar term2))
--sub _ _ _ = error "Could Not Perform Substitution"

{-
The 'isAnElementOf' function checks if something is inside a list, and
returns a Bool, appropriately. It takes 'a', a list of 'a' and returns
a Bool; where 'a' is an instance of Eq. If an empty list is supplied,
then return False, because nothing will match. If 'n' is equal to 'x',
the first item in 'xs', then return True. Otherwise, recursively call
the function on the rest of the list 'xs' 
-}
isAnElementOf :: (Eq a) => a -> [a] -> Bool 
isAnElementOf _ [] = False 
isAnElementOf n (x:xs) 
  | n == x    = True 
  | otherwise = isAnElementOf n xs 

{-
The 'getFirstFreeVariable' will get the first free variable in the
list of available variables that does not conflict with the taken
variables. It gets the first variable via the 'head' function
-}
getFirstFreeVariable :: [Var] -> Var
getFirstFreeVariable usedVariables =
    if (isListEmpty differenceList)
        then (error "Could Not Get A Free Variable")
            else (head differenceList)
    where differenceList = allVariables \\ usedVariables

{-
Checks if a list is null/empty and returns True if the list is empty
-}
isListEmpty :: [Var] -> Bool
isListEmpty list = (if (list == []) then True else False)

{-
The 'allVariables' function returns a list of every single Var.
Initially, I tried `allVariables = ['A'..'Z']`, but quickly realized
that it won't work because 'A' is a Haskell Char
-}
allVariables :: [Var]
allVariables = [A, B, C, D, E, F, G, H, I, J, K, M,
                N, O, P, Q, R, S, U, V, W, X, Y, Z]

{--------------}
{- Question 5 -}
{--------------}

isNF :: Term -> Bool
isNF (Apply (Lambda var term1) term2) = False
isNF (Apply term1 term2) =
    if (isNF term1)
    then (if (isNF term2) then True else False)
    else False
isNF _ = True

{--------------}
{- Question 6 -}
{--------------}

ssos :: Term -> Term
ssos (Apply (Lambda var term1) term2) = sub term1 var term2
ssos (Apply term1 term2) =
    if (isNF term1)
        then isInNormalForm
            else notInNormalForm
    where isInNormalForm = if (isNF term2)
                           then (Apply (term1) (ssos term2))
                           else (Apply (ssos term1) term2)
          notInNormalForm = (Apply term1 term2)
ssos someTerm = someTerm

{--------------}
{- Question 7 -}
{--------------}
eval :: Term -> Term
eval someTerm = if (ssos (someTerm)) == someTerm
    then someTerm else eval(ssos (someTerm))

-----------------------------------------
-- PART 2: IMPLEMENTING SOME FUNCTIONS --
-----------------------------------------

-- Church Boolean True
tru :: Term
tru = Lambda T (Lambda F (Label T))

-- Church Boolean False
fls :: Term
fls = Lambda T (Lambda F (Label F))

logicalNot :: Term
logicalNot = Lambda N (Apply (Apply (Label N) fls) tru)

logicalAnd :: Term
logicalAnd = Lambda A (Lambda N (Apply (Apply (Label A) (Label N)) fls))

logicalOr :: Term
logicalOr = Lambda A (Lambda B (Apply (Apply (Label A) tru) (Label B)))

c0 :: Term
c0 = Lambda S (Lambda Z (Label Z))

c1 :: Term
c1 = Lambda S (Lambda Z (Apply (Label S) (Label Z)))

c2 :: Term
c2 = Lambda S (Lambda Z (Apply (Apply (Label S (Label Z)) (Label S))))

numericSum :: Term
numericSum = Lambda M (Lambda N (Lambda S (Lambda Z (Apply (Apply
    (Label M) (Label S)) (Apply (Apply
    (Label N) (Label S)) (Label Z))))))

numericTimes :: Term
numericTimes = Lambda M (Lambda N (App (App (Label M) Apply (numericSum
    (Label N))) c0))

successor :: Term
successor = Lambda N (Lambda S (Lambda Z (Apply (Apply (Apply
    (Label N) (Label S)) (Label Z)) (Label S))))

predecessor :: Term
predecessor = Lambda M (Apply (Apply (my_fst)
    (Apply (Apply (Label M) (ss)) zz)))

myPair :: Term
myPair = (Lambda F (Lambda S (Lambda B
    (Apply (Apply (Label B (Label F)) (Label S))))))

my_fst :: Term
my_fst = Lambda P (Apply (Label P) tru)

my_snd :: Term
my_snd = Lambda P (Apply (Label P) fls)

ss :: Term
ss = Lambda P (Apply (Apply myPair (Apply my_snd (Label P)))
    (Apply (Apply numericSum c1) (Apply my_snd (Label P))))

zz :: Term
zz = App (App (myPair c0) c0)
