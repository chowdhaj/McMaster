module ExprType where

import           Data.List

data Expr a = Add (Expr a) (Expr a)
            | Mult (Expr a) (Expr a)
            | Const a
            | Var String
  deriving Eq

getVars :: Expr a -> [String]
getVars (Add e1 e2)  = getVars e1 `union` getVars e2
getVars (Mult e1 e2) = getVars e1 `union` getVars e2
getVars (Const _)    = []
getVars (Var ident)  = [ident]
