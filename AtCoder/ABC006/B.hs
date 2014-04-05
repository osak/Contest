{-# LANGUAGE BangPatterns #-}
import Control.Applicative

tribonatti !n !a !b !c | n == 1 = a
                       | n == 2 = b
                       | n == 3 = c
                       | otherwise = tribonatti (n-1) b c ((a+b+c) `mod` 10007)

main = do
  n <- read <$> getLine
  putStrLn $ show $ tribonatti n 0 0 1
