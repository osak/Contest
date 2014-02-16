import Control.Applicative

readInt :: IO Int
readInt = read <$> getLine

main = do
  n <- readInt
  putStrLn $ show $ 2*n
