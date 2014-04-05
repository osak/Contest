check :: Int -> String
check n | n `mod` 3 == 0 = "YES"
        | otherwise      = "NO"

main = do
  n <- getLine
  putStrLn $ check $ read n
