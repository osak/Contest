import Control.Applicative
import qualified Data.ByteString.Char8 as BS
import Data.Array.IO
import Data.Maybe

type Buf = IOUArray Int Int
type Memo = IOUArray Int Bool

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . BS.readInt) <$> (BS.words <$> BS.getLine)

len :: Buf -> IO Int
len arr = snd <$> getBounds arr

calc :: Buf -> Int -> Int -> Memo -> Int -> IO Int
calc arr l r memo acc = do
  lim <- len arr
  if r == lim+1 then
    return acc
  else do
    rv <- readArray arr r
    visited <- readArray memo rv
    if visited then do
      lv <- readArray arr l
      writeArray memo lv False
      calc arr (l+1) r memo acc
    else do
      writeArray memo rv True
      calc arr l (r+1) memo (max (r-l+1) acc)

main :: IO ()
main = do
  n <- read <$> getLine
  aa <- readIntLine
  as <- newListArray (0, n-1) aa
  memo <- newArray (0, 100000) False
  res <- calc as 0 0 memo 0
  putStrLn $ show res
