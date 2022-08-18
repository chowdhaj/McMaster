{- ---------------------------------------------------------------------------------------------------------------
 - README:
 - Follow this instructions execute the test cases used to mark your assignment
 -      - Drop this file and your assignment into a folder together
 -      - Rename YOUR file to Assign1.hs
 -      - Put module Assign1 where at the top of your file (the module must be named this exactly)
 -      - in the terminal, execute runhaskell Test_Assign1
 -      - OR load this file into ghci and call quickCheck on each proposition manually
 -
 - Notes: Make sure to have quickcheck installed, if you don't run the following in terminal
 -        cabal install quickcheck
 - ----------------------------------------------------------------------------------------------------------------
 -}

import Test.QuickCheck
import qualified Assign1 as Student

{- ----------------------------------------------------------------------------------------------------------------
 - Assignment 1 Sample Solution (Verified by quickcheck cubicRealProp)
 - ----------------------------------------------------------------------------------------------------------------
 -}
(***) :: Float -> Float -> Float
x *** y = if x >= 0 then x ** y else -( (-x) ** y)

cubicQ :: Float -> Float -> Float -> Float
cubicQ a b c = let
        x1 = 3 * a * c - b^2
        x2 = 9 * a^2
    in x1 / x2

cubicR :: Float -> Float -> Float -> Float -> Float
cubicR a b c d = let
        x1 = 9 * a * b * c
        x2 = 27 * d * a^2
        x3 = 2 * b^3
        x4 = 54 * a^3
    in (x1 - x2 - x3)  / x4

cubicS :: Float -> Float -> Float
cubicS q r = (r + (q**3 + r**2)**(1/2)) *** (1/3)

cubicT :: Float -> Float -> Float
cubicT q r = (r - (q**3 + r**2)**(1/2)) *** (1/3)

cubicRealSolution :: Float -> Float -> Float -> Float -> Float
cubicRealSolution a b c d = let
        q  = cubicQ a b c
        r  = cubicR a b c d
        s  = cubicS q r
        t  = cubicT q r
    in s + t - b / (3 * a)

{- ----------------------------------------------------------------------------------------------------------------
 -  QuickCheck Properties
 - ----------------------------------------------------------------------------------------------------------------
 -}

{- Test cubicRealSolution
 - ----------------------------------------------------------------------------------------------------------------
 -    Polynomial roots should always be within a reasonable (albeit larger than should be acceptable) tolerance
 -    from 0 when evaluated
 -      Note: Straightforward implementation's of this method are susceptible to very large floating point
 -            error for "tricky" polynomials, and quickCheck is smart and will usually find them
 -            cubicRealProp constrains quickCheck to "easy" polynomials by limiting to integer coefficients
 -}

cubicRealProp :: (Int,Int,Int,Int) -> Bool
cubicRealProp (a',b',c',d') = let
      (a,b,c,d) = (fromIntegral a',fromIntegral b',fromIntegral c',fromIntegral d')
      tol  = 8e-1
      q    = cubicQ a b c
      r    = cubicR a b c d
      x0   = Student.cubicRealSolution a b c d
      z    = hornerEval (a,b,c,d) x0
      cond = q^3 + r^2 > 0 && abs a >= 1
  in (not cond) || (abs z <= tol)

{- Helper Function
 - ----------------------------------------------------------------------------------------------------------------
 - Evaluate given polynomial (a,b,c,d) at x0 using horner's method
 - https://en.wikipedia.org/wiki/Horner%27s_method
 -}
--hornerEval :: (Float,Float,Float,Float) -> Float -> Float
hornerEval (a,b,c,d) x0 = d + x0 * (c + x0 * (b + x0 * a))


{- Test cubicS,cubicT,cubicQ,cubicR
 - ----------------------------------------------------------------------------------------------------------------
 -    If cubicRealProp fails, part marks can be gained if cubicS,cubicT,cubicQ,cubicR compare reasonably
 -    to my own implementation, under proper conditions
 -}

cubicQProp :: (Float,Float,Float) -> Bool
cubicQProp (a,b,c) = let
    tol   = 8e-1
    r0    = Student.cubicQ a b c
    r1    = cubicQ a b c
    cond  = abs a >= 1.0 && r1 > tol
  in (not cond) || (abs (r1-r0) <= tol)

cubicRProp :: (Float,Float,Float,Float) -> Bool
cubicRProp (a,b,c,d) = let
    tol   = 8e-1
    r0    = Student.cubicR a b c d
    r1    = cubicR a b c d
    cond  = abs a > 1.0 && r1 > tol
  in (not cond) || (abs (r1-r0) <= tol)

-- Note: many of you mixed up the order of q and r in the function definition,
--       I cut you some slack and accepted either or
cubicSProp :: (Float,Float) -> Bool
cubicSProp (q,r) = let
    tol   = 8e-1
    s0    = Student.cubicS q r
    s0'   = Student.cubicS r q
    s1    = cubicS q r
    cond  = q^3 + r^2 > tol && s1 > tol
  in (not cond) || (abs (s1-s0) <= tol) || (abs (s1-s0') <= tol)

cubicTProp :: (Float,Float) -> Bool
cubicTProp (q,r) = let
    tol   = 8e-1
    t0    = Student.cubicT q r
    t0'   = Student.cubicT r q
    t1    = cubicT q r
    cond  = q^3 + r^2 > tol &&  t1 > tol
  in (not cond) || (abs (t1-t0) <= tol) || (abs (t1-t0') <= tol)

{- ----------------------------------------------------------------------------------------------------------------
 -  Run test against Assign_1 module in current directory
 - ----------------------------------------------------------------------------------------------------------------
 -}

resultsToMarks results = let
    resultToInt result = case result of
                             Success _ _ _ -> 1
                             _             -> 0
    results' = zipWith (*) [4,2,2,1,1] $ map resultToInt results
    total    = sum results'
  in zipWith (++) ["   cubicRealSolution: "
                  ,"   cubicQ: "
                  ,"   cubicR: "
                  ,"   cubicS: "
                  ,"   cubicT: "
                  ,"   total: "] $ map show $ results' ++ [total]

main = do {
    putStrLn "Testing cubicRealProp: ";
    result_real <- quickCheckResult (withMaxSuccess 100 cubicRealProp);
    putStrLn "Testing cubicQ: ";
    result_q    <- quickCheckResult (withMaxSuccess 100 cubicQProp);
    putStrLn "Testing cubicR: ";
    result_r    <- quickCheckResult (withMaxSuccess 100 cubicRProp);
    putStrLn "Testing cubicS: ";
    result_s    <- quickCheckResult (withMaxSuccess 100 cubicSProp);
    putStrLn "Testing cubicT: ";
    result_t    <- quickCheckResult (withMaxSuccess 100 cubicTProp);
    putStrLn "Marks Assigned: ";
    mapM_ putStrLn (resultsToMarks [result_real,result_q,result_r,result_s,result_t]) }
