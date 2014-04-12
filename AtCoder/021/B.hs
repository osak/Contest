-- Name: Your Numbers are XORed
-- Level: 3
-- Category: 数学
-- Note:

{-
 - b_iの構成方法から、すべてのb_iをxorすると0になる。
 - そのようにならないときは矛盾である。
 -
 - 上の条件を満たす時は常に復元が可能で、かつa_iのうちひとつは任意に決めることができる。
 - （b_1からb_(L-1)までをすべてxorすると a_1^a_L = ^(b_1 ... b_(L-1))となるが、これは条件よりb_Lの式と一致するため、
 -   一次独立な式はL-1本しかない）
 - したがって、a_1を0に決め打つと、xorの性質から簡単に復元できる。
 -}
{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Data.Bits (xor, (.&.))
import qualified Data.ByteString.Char8 as B
import Data.Maybe
import Control.Applicative
import Control.Monad
import Debug.Trace
import Data.List

readInts :: Int -> IO [Int]
readInts n = map (fst . fromJust . B.readInt) <$> replicateM n B.getLine

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . B.readInt) <$> (B.words <$> B.getLine)

main = do
  l <- read <$> getLine
  bs <- readInts l
  if (foldl xor 0 bs) /= 0 then
    putStrLn "-1"
  else
    mapM_ (putStrLn . show) $ init $ scanl xor 0 bs
