{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Data.Bits ((.&.))
import Data.Array.IO
import Control.Monad.ST
import Data.Array.Unboxed
import Control.Applicative
import Control.Monad
import Debug.Trace

type BIT = IOUArray Int Int

readBIT :: BIT -> Int -> IO Int
readBIT _ 0 = return 0
readBIT !bit !i = do 
  a <- readArray bit i
  b <- readBIT bit (i - (i .&. (-i)))
  return $ max a b

addBIT :: BIT -> Int -> Int -> IO ()
addBIT bit !i !v 
  | i > 30000 = return ()
  | i <= 30000 = do org <- readArray bit i
                    writeArray bit i (max org v)
                    addBIT bit (i + (i .&. (-i))) v

readInts :: Int -> IO [Int]
readInts n = map read <$> replicateM n getLine

calc :: BIT -> [Int] -> IO BIT
calc bit [] = return bit
calc !bit !(c:cs) = do
  v <- readBIT bit c
  addBIT bit c (v+1)
  calc bit cs

main = do
  n <- read <$> getLine
  cs <- readInts n
  bit <- newArray (1, 30000) 0
  calc bit cs
  res <- maximum <$> mapM (readBIT bit) [1..n]
  putStrLn $ show $ (n - res)
