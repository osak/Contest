{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Data.Bits ((.&.))
import Data.Array.ST
import Control.Monad.ST
import Data.Array.Unboxed
import Control.Applicative
import Control.Monad
import Debug.Trace

type BIT s = STUArray s Int Int

readBIT :: BIT s -> Int -> ST s Int
readBIT _ 0 = return 0
readBIT !bit !i = do 
  a <- readArray bit i
  b <- readBIT bit (i - (i .&. (-i)))
  return $ max a b

readBIT' :: UArray Int Int -> Int -> Int
readBIT' _ 0 = 0
readBIT' bit i = max (bit!i) (readBIT' bit (i - (i .&. (-i))))

addBIT :: BIT s -> Int -> Int -> ST s ()
addBIT bit !i !v 
  | i > 30000 = return ()
  | i <= 30000 = do org <- readArray bit i
                    writeArray bit i (max org v)
                    addBIT bit (i + (i .&. (-i))) v

readInts :: Int -> IO [Int]
readInts n = map read <$> replicateM n getLine

calc :: BIT s -> [Int] -> ST s (BIT s)
calc bit [] = return bit
calc !bit !(c:cs) = do
  v <- readBIT bit c
  addBIT bit c (v+1)
  calc bit cs

main = do
  n <- read <$> getLine
  cs <- readInts n
  let lis = runSTUArray $ do
              bit <- newArray (1, 30000) 0
              calc bit cs
  let res = maximum $ map (readBIT' lis) [1..n]
  putStrLn $ show $ (n - res)
