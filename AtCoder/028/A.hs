-- Name: 小石を取るゲーム
-- Level: 1
-- Category: シミュレーション
-- Note:

{-
 - 問題に書いてある通りにシミュレーションすればよい。
 -}
{-# LANGUAGE BangPatterns #-}
import Control.Monad
import Control.Applicative
import Data.Maybe
import Data.Array.IO
import qualified Data.ByteString.Char8 as BS

readInt :: IO Int
readInt = fst . fromJust . BS.readInt <$> BS.getLine

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . BS.readInt) <$> (BS.words <$> BS.getLine)

sim :: Int -> Int -> Int -> String
sim n a b = ant n
  where
    ant x | x <= a = "Ant"
          | otherwise = bug (x-a)
    bug x | x <= b = "Bug"
          | otherwise = ant (x-b)

main :: IO ()
main = do
  n:a:b:_ <- readIntLine
  putStrLn $ sim n a b
