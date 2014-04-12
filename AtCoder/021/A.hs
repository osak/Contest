--Name: DEAD END
--Level: 2
--Category: シミュレーション
--Note:

{-
 - 縦横全ての方向について、同じ数字が連続している箇所を調べる。
 -}
{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import qualified Data.ByteString.Char8 as B
import Data.Maybe
import Control.Applicative
import Control.Monad
import Debug.Trace
import Data.List

readInts :: Int -> IO [Int]
readInts n = map (fst . fromJust . B.readInt) <$> replicateM n B.getLine

readWords :: IO [B.ByteString]
readWords = B.words <$> B.getLine

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . B.readInt) <$> readWords

check [] _ = False
check _ [] = False
check (a:as) (b:bs) | a == b = True
                    | otherwise = check as bs

checkRow [] = False
checkRow (row:rows) 
  | check row (tail row) = True
  | check (tail row) row = True
  | otherwise = checkRow rows

checkCol = checkRow . transpose

main = do
  field <- replicateM 4 readIntLine
  if (checkRow field) || (checkCol field) then
    putStrLn "CONTINUE"
  else
    putStrLn "GAMEOVER"
