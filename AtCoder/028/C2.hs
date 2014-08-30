{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Control.Monad
import Control.Applicative
import Data.Maybe
import Data.Array.IO
import Data.List
import qualified Data.ByteString.Char8 as BS
import qualified Data.Map as M
import Control.Monad.State
import Control.Monad.Primitive
import Debug.Trace

type Tree = M.Map Int [Int]
type Buf = IOUArray Int Int

readInt :: IO Int
readInt = fst . fromJust . BS.readInt <$> BS.getLine

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . BS.readInt) <$> (BS.words <$> BS.getLine)

readParent :: Tree -> Int -> IO Tree
readParent !tree i = do
  parent <- readInt
  let m1 = M.insertWith (\x y -> (head x) : y) i [parent] tree
  let m2 = M.insertWith (\x y -> (head x) : y) parent [i] m1
  return m2

tour :: Tree -> [(Int,Int)]
tour tree = go [(0, (-1))]
  where
    go [] = []
    go (cur@(pos,parent):rem) =
      let !cs = filter (/= parent) (tree M.! pos)
          !stk = foldl' (\a c -> (c,pos) : a) rem cs
      in cur : go stk

main :: IO ()
main = do
  n <- readInt
  tree <- foldM readParent M.empty [1..n-1]
  size <- newArray (0, n-1) 0 :: IO Buf
  balance <- newArray (0, n-1) 0 :: IO Buf
  let !ord = reverse $ tour tree
  forM_ ord $ \(i,parent) -> do
    -- Calc balance
    let cs = filter (/= parent) (tree M.! i)
    cbs <- mapM (readArray size) cs
    writeArray balance i (maximum $ (n - 1 - sum cbs) : cbs)
    -- Calc size
    writeArray size i (1 + sum cbs)
  forM_ [0..n-1] $ \i -> (readArray balance i) >>= print
