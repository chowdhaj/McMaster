import Data.List
import Debug.Trace

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
  
data V = Tru | Fls | Z | SuccNV V | UnitV | Location Loc | Var Label | L Label Type T deriving(Show, Eq)
  
data Label = A | C | D | E | F | G | H | I | J | K 
    | M | O | P | Q | R | S | U | W | X | Y  
    deriving (Show, Eq)
    
data Loc = L0 | L1 | L2 | L3 | L4 | L5 | L6 | L7 | L8 | L9
    deriving (Show, Eq)

data Type = BOOL | NAT | Unit | Arrow Type Type | Ref Type deriving (Show, Eq)

type Gamma = [(Label, Type)] 

type Mu = [(Loc, V)]

freeVars :: T -> [Label] 

relabel :: T -> Label -> Label -> T 

sub :: T -> Label -> T -> T 

isNF :: T -> Bool 

ssos :: (T, Mu) -> (T, Mu)

typeCheck :: Gamma -> T -> Maybe Type

eval :: T -> T 

run :: T -> T
