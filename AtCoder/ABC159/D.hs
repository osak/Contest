{-# LANGUAGE OverloadedStrings #-} 
import qualified Data.Text as T
import qualified Data.Text.IO as I
import qualified Data.Map.Strict as M
import Data.Map.Strict ((!))
import Control.Monad

comb :: Int -> Int
comb n = n*(n-1) `div` 2

main :: IO ()
main = do
  line <- I.getLine
  let n = read $ T.unpack line :: Int

  line2 <- I.getLine
  let as = map (read . T.unpack) $ T.splitOn " " line2 :: [Int]
  let m = foldr (M.alter (\v -> Just $ (maybe 0 id v) + 1)) M.empty as :: M.Map Int Int
  let mm = M.map comb m :: M.Map Int Int
  let total = sum $ M.elems mm

  let ans = map (\i -> total - (mm ! i) + comb ((m ! i) - 1)) as :: [Int]
  forM_ ans print