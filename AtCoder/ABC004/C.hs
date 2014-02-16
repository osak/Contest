import Control.Applicative
import Data.List

readInt :: IO Int
readInt = read <$> getLine

中野 梓 にゃん = let (ネコミミ,しっぽ) = splitAt (にゃん+1) 梓
                 in (tail' ネコミミ) ++ [head 梓] ++ しっぽ
  where
    tail' [] = []
    tail' x = tail x

azcat = concat

main = do
  n <- readInt
  let あず = n `div` 5 `mod` 6 + 1
  let にゃん = n `mod` 5
  let 梓 = [あず .. 6] ++ [1 .. あず-1]
  putStrLn $ azcat $ map show $ 中野 梓 にゃん
