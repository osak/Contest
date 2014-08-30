-- Name: 高橋王国の分割統治
-- Level: 3
-- Category: 木,Tree,DFS,深さ優先探索
-- Note:

{-
 - アルゴリズムはRuby解を参照のこと。
 -}
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

type Tree = IOArray Int [Int]
type Buf = IOUArray Int Int

readInt :: IO Int
readInt = fst . fromJust . BS.readInt <$> BS.getLine

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . BS.readInt) <$> (BS.words <$> BS.getLine)

readParent :: Tree -> Int -> IO ()
readParent !tree i = do
  parent <- readInt
  readArray tree i >>= writeArray tree i . (parent :)
  readArray tree parent >>= writeArray tree parent . (i :)

tour :: Tree -> IO [(Int,Int)]
tour tree = go [(0, (-1))]
  where
    go [] = return []
    go (cur@(pos,parent):rem) = do
      !cs <- fmap (filter (/= parent)) (readArray tree pos)
      let !stk = foldl' (\a c -> (c,pos) : a) rem cs
      go stk >>= return . (cur:)

main :: IO ()
main = do
  n <- readInt
  tree <- newArray (0, n-1) [] :: IO Tree
  mapM_ (readParent tree) [1..n-1]
  size <- newArray (0, n-1) 0 :: IO Buf
  balance <- newArray (0, n-1) 0 :: IO Buf
  !ord <- fmap reverse $ tour tree
  forM_ ord $ \(i,parent) -> do
    -- Calc balance
    cs <- fmap (filter (/= parent)) $ readArray tree i
    cbs <- mapM (readArray size) cs
    writeArray balance i (maximum $ (n - 1 - sum cbs) : cbs)
    -- Calc size
    writeArray size i (1 + sum cbs)
  forM_ [0..n-1] $ \i -> (readArray balance i) >>= print
