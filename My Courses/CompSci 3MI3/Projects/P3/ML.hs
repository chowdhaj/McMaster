{-
AUTHOR  :: Jatin Chowdhary
MACID   :: Chowdhaj
COURSE  :: CompSci 3MI3
DATE    :: December 8th, 2021
LICENSE :: GPL
-}

import Data.List
import Debug.Trace

-- I had to define a main function, otherwise it wouldn't compile
-- Please delete if it bothers you or if it is not necessary
main :: IO ()
main = return ()

data T = App T T
       | If T T T 
       | Succ T
       | Pred T
       | IsZero T
       | Val V
       | Let Label T T
       | Seq T T
       | Alloc T
       | DeRef T
       | Assign T T 
  deriving (Show, Eq)
  
data V = Tru | Fls | Z | SuccNV V | UnitV | Location Loc | Var Label |
         L Label Type T
    deriving(Show, Eq)
  
data Label = A | C | D | E | F | G | H | I | J | K  | M | O | P | Q |
             R | S | U | W | X | Y  
    deriving (Show, Eq)

data Loc = L0 | L1 | L2 | L3 | L4 | L5 | L6 | L7 | L8 | L9
    deriving (Show, Eq)

data Type = BOOL | NAT | Unit | Arrow Type Type | Ref Type
    deriving (Show, Eq)

type Gamma = [(Label, Type)] 

type Mu = [(Loc, V)]

{-
freeVars :: Returns a list of all the free variables in a term
-}
freeVars :: T -> [Label]
freeVars (App term1 term2) = (union (freeVars term1) (freeVars term2))
freeVars (Val (Var x)) = [x]
freeVars (Val (L label termType term)) = (freeVars term) \\ [label]
freeVars (If term1 term2 term3) =
    (union (freeVars term3) (union (freeVars term1) (freeVars term2)))
freeVars (IsZero term) = (freeVars term)
freeVars (Pred term) = (freeVars term)
freeVars (Succ term) = (freeVars term)
freeVars (Let labels term1 term2) =
    (union (freeVars term1) (freeVars term2)) \\ [labels]
freeVars (Seq term1 term2) = (union (freeVars term1) (freeVars term2))
freeVars (Alloc term) = (freeVars term)
freeVars (DeRef term) = (freeVars term)
freeVars (Assign term1 term2) =
    (union (freeVars term1) (freeVars term2))
freeVars _ = []
-- For any other case that is not covered, just return the empty list

{-
relabel :: Replaces all occurrences of a label with a different one
-}
relabel :: T -> Label -> Label -> T
relabel (Val (Var label)) replaceLabel newLabel =
    if (label == replaceLabel)
        then (Val (Var newLabel))
            else (Val (Var label))
relabel (Val (L label termType term)) replaceLabel newLabel =
    if (label == replaceLabel)
        then (Val (L newLabel termType relabelTerm))
            else (Val (L label termType relabelTerm))
    where relabelTerm = (relabel term replaceLabel newLabel)
relabel (App term1 term2) replaceLabel newLabel =
    App (relabel term1 replaceLabel newLabel)
        (relabel term2 replaceLabel newLabel)
relabel (If term1 term2 term3) replaceLabel newLabel =
    If (relabel term1 replaceLabel newLabel)
       (relabel term2 replaceLabel newLabel)
       (relabel term3 replaceLabel newLabel)
relabel (IsZero term) replaceLabel newLabel =
    IsZero (relabel term replaceLabel newLabel)
relabel (Pred term) replaceLabel newLabel =
    Pred (relabel term replaceLabel newLabel)
relabel (Succ term) replaceLabel newLabel =
    Succ (relabel term replaceLabel newLabel)
relabel (Let label term1 term2) replaceLabel newLabel =
    if (label == replaceLabel)
        then (Let replaceLabel relabelTerm1 relabelTerm2)
            else (Let label relabelTerm1 relabelTerm2)
    where relabelTerm1 = (relabel term1 replaceLabel newLabel)
          relabelTerm2 = (relabel term2 replaceLabel newLabel)
relabel (Seq term1 term2) replaceLabel newLabel =
    Seq (relabel term1 replaceLabel newLabel)
        (relabel term2 replaceLabel newLabel)
relabel (Alloc term) replaceLabel newLabel =
    Alloc (relabel term replaceLabel newLabel)
relabel (DeRef term) replaceLabel newLabel =
    DeRef (relabel term replaceLabel newLabel)
relabel (Assign term1 term2) replaceLabel newLabel =
    Assign (relabel term1 replaceLabel newLabel)
           (relabel term2 replaceLabel newLabel)
relabel edgeCase _ _ = edgeCase
-- For any other case that is not covered, just return the T

{-
allLabels :: Returns a list of all labels defined by the 'Label' data
-}
allLabels :: [Label]
allLabels = [A, C, D, E, F, G, H, I, J, K , M, O, P, Q, R, S, U,
             W, X, Y]

{-
getAvailableLabel :: Returns a free label from the list of all labels
-}
getAvailableLabel :: [Label] -> Label
getAvailableLabel existingLabels =
    if (null availableLabels)
        then error "No More Available Variables!"
            else last availableLabels
    where availableLabels = (allLabels \\ existingLabels)

{-
sub :: Performs substitution on the given Term
-}
sub :: T -> Label -> T -> T
sub (Val (Var label)) current new =
    if (label == current) then new else Val (Var label)
sub (App term1 term2) current new =
    App (sub term1 current new) (sub term2 current new)
sub (Val (L label termType term)) current new =
    if (label == current) then (Val (L label termType term)) else
        (if (elem (label) (freeVars new))
         then (Val (L subNewLabel termType (sub subRelabel current
                                                                new)))
         else (Val (L label termType (sub term current new))))
    where subNewLabel = getAvailableLabel (freeVars new)
          subRelabel  = (relabel term label subNewLabel)
sub (If term1 term2 term3) current new =
    If (sub term1 current new)
       (sub term2 current new)
       (sub term3 current new)
sub (IsZero term) current new = IsZero (sub term current new)
sub (Pred term) current new = Pred (sub term current new)
sub (Succ term) current new = Succ (sub term current new)
sub (Let label term1 term2) current new =
    if (label == current) then (Let label subOnTerm term2) else
        (if (elem (label) (freeVars new))
         then (Let subNewLabel subOnTerm (sub subRelabel current new))
         else (Let label subOnTerm (sub term2 current new)))
    where subOnTerm   = (sub term1 current new)
          subNewLabel = (getAvailableLabel (freeVars new))
          subRelabel  = (relabel term2 label subNewLabel)
sub (Seq term1 term2) current new =
    Seq (sub term1 current new) (sub term2 current new)
sub (Alloc term1) current new = Alloc (sub term1 current new)
sub (DeRef term1) current new = DeRef (sub term1 current new)
sub (Assign term1 term2) current new =
    Assign (sub term1 current new) (sub term2 current new)
sub edgeCase _ _ = edgeCase
-- For any other case that is not covered, just return the T

{-
isNF :: Determine if the Term is in normal form and return a Bool
-}
isNF :: T -> Bool
isNF (App (Val (L label termType term1)) term2) = False
isNF (App term1 term2) =
    if ((isNF term1) && (isNF term2)) then True else False
isNF (If (Val v) term2 term3) =
    if (v == Tru) then True else
        (if (v == Fls) then True else False)
isNF (If term1 term2 term3) =
    (isNF term1) && (isNF term2) && (isNF term3)
isNF (IsZero (Val label)) = False
isNF (IsZero term) = if (isNF term) then True else False
isNF (Pred (Val label)) = False
isNF (Pred term) = if (isNF term) then True else False
isNF (Succ (Val label)) = False
isNF (Succ term) = if (isNF term) then True else False
isNF (Let label (Val x) term) = False
isNF (Let label term1 term2) =
    if ((isNF term1) && (isNF term2)) then True else False
isNF (Seq (Val UnitV) term) = False
isNF (Seq term1 term2) =
    if ((isNF term1) && (isNF term2)) then True else False
isNF (Alloc (Val x)) = False
isNF (Alloc term) = if (isNF term) then True else False
isNF (DeRef (Val (Location mem))) = False
isNF (DeRef term) = if (isNF term) then True else False
isNF (Assign (Val (Location mem)) (Val x)) = False
isNF (Assign term1 term2) =
    if ((isNF term1) && (isNF term2)) then True else False
--isNF (Val _) = False -- This is incorrect
isNF _   = True
-- Anything not defined is assumed to be in normal form (True)

{-
allMemoryLocations :: Returns a list of all memory locations
-}
allMemoryLocations :: [Loc]
allMemoryLocations = ([L0, L1, L2, L3, L4, L5, L6, L7, L8, L9])

{-
getLocationsInMu :: Get all memory locations in `mu`
-}
getLocationsInMu :: Mu -> [Loc]
getLocationsInMu [] = []
getLocationsInMu ((location, value) : m_u) =
    location : (getLocationsInMu m_u)
-- getLocationsInMu _ = error "ERROR: Corrupted Memory Exception"
-- No need for this, because pattern match is redundant

{-
getNewMemoryLocation :: Return a new and unused memory location
-}
getNewMemoryLocation :: Mu -> Loc
getNewMemoryLocation m_u =
    if (noMoreAvailableLocations)
        then error ("ERROR: Out Of Memory")
            else (last availableMemoryLocations)
    where unavailableMemoryLocations = (getLocationsInMu m_u)
          availableMemoryLocations   = (allMemoryLocations \\
                                           unavailableMemoryLocations)
          noMoreAvailableLocations   = null availableMemoryLocations

{-
getValueAtLocation :: Return the value at a location in memory
-}
getValueAtLocation :: Mu -> Loc -> Maybe V
getValueAtLocation [] location = Nothing
getValueAtLocation ((location1, value) : m_u) location2 =
    if (location1 == location2)
        then (Just value)
            else (getValueAtLocation m_u location2)

{-
substitutionForMu :: Substitute (val, loc) in `mu` with a new one
-}
substitutionForMu :: Mu -> Loc -> V -> Mu
substitutionForMu [] _ _ = []
substitutionForMu ((currentLoc, currentVal) : m_u) newLoc newVal =
    if (currentLoc == newLoc)
        then ((newLoc, newVal): m_u)
            else ((newLoc, newVal) :
                                (substitutionForMu m_u newLoc newVal))

{-
unwrapMaybeV :: Helper function to extract from Maybe V
-}
unwrapMaybeV :: Maybe V -> V
unwrapMaybeV (Just x) = x
unwrapMaybeV (Nothing) = error "ERROR: No Type Exception"

{-
ssos :: Small Step Operational Semantics
-}
ssos :: (T, Mu) -> (T, Mu)
-- E-If-True
ssos ((If (Val Tru) term2 term3), m_u) = (term2, m_u)
-- E-If-False
ssos ((If (Val Fls) term2 term3), m_u) = (term3, m_u)
-- E-If
ssos ((If term1 term2 term3), m_u) =
    if ((isNF term1) == True)
        then ((If term1 term2 term3), m_u)
            else ((If newTerm1 term2 term3), new_mu)
    where newTerm1 = fst (ssos (term1, m_u))
          new_mu   = snd (ssos (term1, m_u))
-- E-Reflexivity-Succ-NV -- I made up this name
ssos ((Succ (Val v)), m_u) = ((Val (SuccNV v)), m_u)
-- E-Succ
ssos ((Succ term), m_u) =
    if (isNF term)
        then ((Succ term), m_u)
            else ((Succ newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-Pred-Zero
ssos (Pred (Val Z), m_u) = (Val Z, m_u)
-- E-Pred-Succ(NV)
ssos ((Pred (Val (SuccNV vls))), m_u) = (Val vls, m_u)
-- E-Pred
ssos ((Pred term), m_u) =
    if (isNF term)
        then ((Pred term), m_u)
            else ((Pred newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-Is-Zero-Zero
ssos ((IsZero (Val Z)), m_u) = (Val Tru, m_u)
-- E-Is-Zero-Succ
ssos ((IsZero (Val (SuccNV vls))), m_u) = (Val Fls, m_u)
-- E-App-Abs
ssos ((App (Val (L label termType term)) (Val var)), m_u) =
    (sub term label (Val var), m_u)
-- E-App2
ssos ((App (Val var) term), m_u) =
    if (isNF term)
        then ((App (Val var) term), m_u)
            else ((App (Val var) newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-App1
ssos ((App term1 term2), m_u) =
    if (isNF term1)
        then ((App term1 term2), m_u)
            else ((App newTerm term2), new_mu)
    where newTerm = fst (ssos (term1, m_u))
          new_mu  = snd (ssos (term1, m_u))
-- E-Let-V
ssos ((Let label (Val val) term), m_u) =
    (sub term label (Val val), m_u)
-- E-Let
ssos ((Let label term1 term2), m_u) =
    if (isNF term1)
        then ((Let label term1 term2), m_u)
            else ((Let label newTerm1 term2), new_mu)
    where newTerm1 = fst (ssos (term1, m_u))
          new_mu   = snd (ssos (term1, m_u))
-- E-Seq-Next
ssos ((Seq (Val UnitV) term), m_u) = (term, m_u)
-- E-Seq
ssos ((Seq term1 term2), m_u) =
    if (isNF term1)
        then ((Seq term1 term2), m_u)
            else ((Seq newTerm1 term2), new_mu)
    where newTerm1 = fst (ssos (term1, m_u))
          new_mu   = snd (ssos (term1, m_u))
-- E-Ref-V
ssos ((Alloc (Val v)), m_u) =
    (Val (Location newLocation), (newLocation, v) : m_u)
        where newLocation = (getNewMemoryLocation m_u)
-- E-Ref
ssos ((Alloc term), m_u) =
    if (isNF term)
        then ((Alloc term), m_u)
            else ((Alloc newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-DeRefLoc
ssos (DeRef (Val (Location mem)), m_u) =
    if (isMemoryEmpty)
        then (DeRef (Val (Location mem)), m_u)
            else (Val (unwrapMaybeV valueInMemory), m_u)
    where valueInMemory   = (getValueAtLocation m_u mem)
          isMemoryEmpty   = if ((valueInMemory) == Nothing)
                            then True
                            else False
          -- unwrap (Just x) = x
          -- unwrap valueInMemory
-- E-DeRef
ssos ((DeRef term), m_u) =
    if (isNF term)
        then ((DeRef term), m_u)
            else ((DeRef newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-Assign
ssos ((Assign (Val (Location loc)) (Val v)), m_u) =
    ((Val UnitV), (substitutionForMu m_u loc v))
-- E-Assign2
ssos ((Assign (Val v) term), m_u) =
    if (isNF term)
        then ((Assign (Val v) term), m_u)
            else ((Assign (Val v) newTerm), new_mu)
    where newTerm = fst (ssos (term, m_u))
          new_mu  = snd (ssos (term, m_u))
-- E-Assign1
ssos ((Assign term1 term2), m_u) =
    if (isNF term1)
        then ((Assign term1 term2), m_u)
            else ((Assign newTerm1 term2), new_mu)
    where newTerm1 = fst (ssos (term1, m_u))
          new_mu   = snd (ssos (term1, m_u))
-- E-Edge-Case (Not part of SSOS)
ssos edgeCase = edgeCase

{-
unwrapMaybeType :: Helper function to extract type of Maybe
-}
unwrapMaybeType :: Maybe Type -> Type
unwrapMaybeType (Just x) = x
unwrapMaybeType (Nothing) = error "ERROR: No Type Exception"

{-
getTypeOfVariable :: Helper function to get type of variable
-}
getTypeOfVariable :: Label -> Gamma -> Maybe Type
getTypeOfVariable _ [] = Nothing
getTypeOfVariable label ((location, types) : gamma) =
    if (label == location)
        then (Just types)
            else (getTypeOfVariable label gamma)

{-
getArrowType :: Get type of a specified term of an Arrow
-}
getArrowType :: Int -> Type -> Maybe Type
getArrowType 1 (Arrow term1 term2) = (Just term1)
getArrowType 2 (Arrow term1 term2) = (Just term2)
getArrowType _ (Arrow term1 term2) = Nothing

{-
isNothing :: Determine if type of Term is Nothing
-}
isNothing :: Gamma -> T -> Bool
isNothing gamma term =
    if ((typeCheck gamma term) == Nothing) then True else False
-- isNothing _ _ = error "ERROR: Incorrect Term Exception"
-- This last case is not needed because it is redundant

{-
isNat :: Helper function to determine if type of Term is NAT
-}
isNat :: Gamma -> T -> Bool
isNat gamma term =
    if ((typeCheck gamma term) == (Just NAT)) then True else False
-- isNat _ _ = error "ERROR: Incorrect Term Exception"
-- This last case is not needed because it is redundant

{-
isBool :: Helper function to determine if type of Term is Bool
-}
isBool :: Gamma -> T -> Bool
isBool gamma term =
    if ((typeCheck gamma term) == (Just BOOL)) then True else False
-- isBool _ _ = error "ERROR: Incorrect Term Exception"
-- This last case is not needed because it is redundant

{-
isJustUnit :: Helper function to determine if term is `Just Unit`
-}
isJustUnit :: Gamma -> T -> Bool
isJustUnit gamma term =
    if ((typeCheck gamma term) == (Just Unit)) then True else False
-- isJustUnit _ _ = error "ERROR: Incorrect Term Exception"
-- This last case is not needed because it is redundant

{-
areTypesEqual :: Determine if the types of 2 terms are equal
-}
areTypesEqual :: Gamma -> T -> T -> Bool
areTypesEqual gamma term1 term2 =
    if (typeCheckTerm1 == typeCheckTerm2) then True else False
        where typeCheckTerm1 = (typeCheck gamma term1)
              typeCheckTerm2 = (typeCheck gamma term2)

{-
getReferenceType :: Helper function to return type of reference
-}
getReferenceType :: Maybe Type -> Maybe Type
getReferenceType (Just (Ref reference)) = Just reference
getReferenceType other = Nothing

{-
typeCheck :: Type Checking Function
-}
typeCheck :: Gamma -> T -> Maybe Type
-- T-If
typeCheck gamma (If term1 term2 term3) =
    if (isTermBool1) && (not (isTermNothing2)) && (checkTypeTerm3)
        then getTypeTerm2
            else Nothing
    where isTermBool1    = (isBool gamma term1)
          isTermNothing2 = (isNothing gamma term2)
          checkTypeTerm3 = (areTypesEqual gamma term1 term2)
          getTypeTerm2   = (typeCheck gamma term2)
-- T-True
typeCheck gamma (Val Tru) = (Just BOOL)
-- T-False
typeCheck gamma (Val Fls) = (Just BOOL)
-- T-Succ
typeCheck gamma (Succ term) =
    if isTermNothing then Nothing else
        (if isTermNatType then (Just NAT) else Nothing)
            where isTermNothing = (isNothing gamma term)
                  isTermNatType = (isNat gamma term)
-- T-Pred
typeCheck gamma (Pred term) =
    if isTermNothing then Nothing else
        (if isTermNatType then (Just NAT) else Nothing)
            where isTermNothing = (isNothing gamma term)
                  isTermNatType = (isNat gamma term)
-- T-Is-Zero
typeCheck gamma (IsZero term) =
    if isTermNothing then Nothing else
        (if isTermNatType then (Just BOOL) else Nothing)
            where isTermNothing = (isNothing gamma term)
                  isTermNatType = (isNat gamma term)
-- T-Zero
typeCheck gamma (Val Z) = Just NAT
-- T-Var
typeCheck gamma (Val (Var val)) = (getTypeOfVariable val gamma)
-- T-Abs
typeCheck gamma (Val (L label termType term)) =
    if (maybeType == Nothing) then Nothing else justValue
        where maybeType = typeCheck ((label, termType) : gamma) term
              justValue = Just (Arrow termType (unwrapMaybeType
                                                           maybeType))
-- T-App
typeCheck gamma (App term1 term2) =
    if areTermsNothing then Nothing else
        (if (firstArrowType == getTermType2)
            then Nothing
                else Nothing)
    where isTermNothing1  = (isNothing gamma term1)
          isTermNothing2  = (isNothing gamma term2)
          areTermsNothing = (isTermNothing1 || isTermNothing2)
          getTermType1    = (typeCheck gamma term1)
          getTermType2    = (typeCheck gamma term2)
          firstArrowType  = (getArrowType 1
                                (unwrapMaybeType getTermType1))
          secondArrowType = (getArrowType 2
                                (unwrapMaybeType getTermType1))
-- T-Unit
typeCheck gamma (Val UnitV) = Just Unit
-- T-Ref
typeCheck gamma (Let label (Alloc term1) term2) =
    if isTermNothing1 then Nothing else getTermType2
        where isTermNothing1 = (isNothing gamma term1)
              getTermType1   = (typeCheck gamma term1)
              getTermType2   = (typeCheck ((label, (Ref
                      (unwrapMaybeType getTermType1))) : gamma) term2)
-- T-Let
typeCheck gamma (Let label term1 term2) =
    if isTermNothing1 then Nothing else getTermType2
        where isTermNothing1 = (isNothing gamma term1)
              getTermType1   = (typeCheck gamma term1)
              getTermType2   = (typeCheck ((label,
                       (unwrapMaybeType getTermType1)) : gamma) term2)
-- T-Seq
typeCheck gamma (Seq term1 term2) =
    if isTermJustUnit then getTermType2 else Nothing
        where isTermJustUnit = (isJustUnit gamma term1)
              getTermType2   = (typeCheck gamma term2)
-- T-DeRef
typeCheck gamma (DeRef term) = (getReferenceType getTermType)
    where getTermType = (typeCheck gamma term)
-- T-Assign
typeCheck gamma (Assign term1 term2) =
    if ((not isTermNothing2) && checkTypeTerm1)
        then Just Unit
            else Nothing
    where isTermNothing2 = (isNothing gamma term2)
          getTermType1   = (typeCheck gamma term1)
          getTermType2   = (typeCheck gamma term2)
          checkTypeTerm1 = (getTermType1 == Just (Ref
                                      (unwrapMaybeType getTermType2)))
-- T-Edge-Case (Not Part Of TypeCheck)
typeCheck gamma _ = Nothing

{-
subEval :: Evaluates the inner portion of the specified term
-}
subEval :: (T, Mu) -> (T, Mu)
subEval (term, m_u) =
    if (stepped == (term, m_u))
        then (term, m_u) else
            (subEval (stepped))
    where stepped = ssos (term, m_u)

{-
eval :: Function to evaluate the given term
-}
eval :: T -> T 
eval term = fst (subEval (term, []))

{-
run :: Initial function to type check and evaluate a specified term
-}
run :: T -> T
run term =
    if ((typeCheck [] term) == Nothing)
        then (error "Type Mismatch Exception")
            else (eval term)
