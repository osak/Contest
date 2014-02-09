-- Name: 解像度が低い。
-- Level: 2
-- Category: やるだけ
-- Note:
--
-- 先頭から順に値を見ていき、増加が連続している回数を数えて、
-- これがk以上になる回数を数える。
-- オーダーはO(N)。

{-# OPTIONS_GHC -O2 #-}
{-# LANGUAGE BangPatterns #-}
import Data.Char (isSpace)
import qualified Data.ByteString.Char8 as B

newtype Scanner a = Scanner (B.ByteString -> (B.ByteString, a))
instance Monad Scanner where
  return a = Scanner $ \t -> (t, a)
  s >>= f = s `seq` Scanner $ \l -> 
              let (rem, val) = evalScanner s l
                  s' = f val
              in evalScanner s' rem

evalScanner :: Scanner a -> B.ByteString -> (B.ByteString, a)
evalScanner (Scanner f) = f

trim :: B.ByteString -> B.ByteString
trim = B.dropWhile isSpace

isLineSep :: Char -> Bool
isLineSep '\n' = True
isLineSep '\r' = True
isLineSep _ = False

readInt :: Scanner Int
readInt = Scanner $ \l -> let (tok, rem) = B.break isSpace l
                          in (trim rem, read $ B.unpack tok)

readLine :: Scanner B.ByteString
readLine = Scanner $ \l -> let (tok, rem) = B.break isLineSep l
                           in (trim rem, tok)

runScanner :: Scanner a -> B.ByteString -> a
runScanner s t = snd $ evalScanner s (trim t)

solve = runScanner $ do
  n <- readInt
  k <- readInt
  as <- mapM (\_ -> readInt) [1 .. n]
  --return $ scanl go 0 (zip (0:as) as)
  return $ length $ filter (>= k) $ scanl go 0 (zip (0:as) as)
  where
    go :: Int -> (Int,Int) -> Int
    go acc (prev,cur) | prev < cur = acc + 1
                      | otherwise = 1

main = do
  txt <- B.getContents
  let a = solve txt
  putStrLn $ show a
