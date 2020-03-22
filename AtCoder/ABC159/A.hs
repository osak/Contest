{-# LANGUAGE OverloadedStrings #-} 
import qualified Data.Text as T
import qualified Data.Text.IO as I

comb :: Int -> Int
comb n = n*(n-1) `div` 2

main :: IO ()
main = do
  line <- I.getLine
  let tokens = T.splitOn " " line
  let nums = map (read . T.unpack) tokens
  let ans = comb (head nums) + comb (nums !! 1)
  print ans