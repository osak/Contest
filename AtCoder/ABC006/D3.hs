{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Data.Bits ((.&.))
import qualified Data.Vector.Unboxed.Mutable as UM
import qualified Data.ByteString.Char8 as B
import Data.Maybe
import Control.Applicative
import Control.Monad
import Debug.Trace

type BIT = UM.IOVector Int

readBIT :: BIT -> Int -> IO Int
readBIT _ 0 = return 0
readBIT !bit !i = do 
  a <- UM.read bit i
  b <- readBIT bit (i - (i .&. (-i)))
  return $ max a b

addBIT :: BIT -> Int -> Int -> IO ()
addBIT bit !i !v 
  | i > 30000 = return ()
  | i <= 30000 = do org <- UM.read bit i
                    UM.write bit i (max org v)
                    addBIT bit (i + (i .&. (-i))) v

readInts :: Int -> IO [Int]
readInts n = map (fst . fromJust . B.readInt) <$> replicateM n B.getLine

calc :: BIT -> [Int] -> Int -> IO Int
calc bit [] acc = return acc
calc !bit !(c:cs) acc = do
  v <- readBIT bit c
  addBIT bit c (v+1)
  calc bit cs (max acc (v+1))

main = do
  n <- read <$> getLine
  cs <- readInts n
  bit <- UM.replicate 30001 0
  res <- calc bit cs 0
  putStrLn $ show $ (n - res)
