{-# LANGUAGE OverloadedStrings #-} 
import qualified Data.Text as T
import qualified Data.Text.IO as I

isPalindrome :: T.Text -> Bool
isPalindrome t
  | T.length t <= 1 = True
  | T.head t == T.last t = isPalindrome $ T.init $ T.tail t
  | otherwise = False

main :: IO ()
main = do
    line <- I.getLine
    let len = T.length line
    let halfLen = (len - 1) `div` 2
    let ans = isPalindrome line && isPalindrome (T.take halfLen line) && isPalindrome (T.drop (halfLen+1) line)
    putStrLn $ if ans then "Yes" else "No"