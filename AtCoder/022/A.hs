import Control.Applicative
import Data.Char

check [] _ = True
check pat@(x:xs) (c:str) | x == c = check xs str
                         | otherwise = check pat str
check _ _ = False

main = do
  s <- map toUpper <$> getLine
  putStrLn $ if check "ICT" s then "YES" else "NO"
