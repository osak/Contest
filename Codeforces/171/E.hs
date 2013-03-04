calc :: String -> Int
calc str = go 0 str
    where
    go acc [] = acc
    go acc (d:ds) | d == '0' = go acc $ dropWhile (== '0') ds
                  | d == '1' = case ds of
                                [] -> acc+1
                                ('0':ds') -> go (acc+1) ds'
                                ('1':ds') -> go (acc+1) $ roundup ds
    roundup ds = case dropWhile (== '1') ds of
                    [] -> "1"
                    (d:ds') -> '1' : ds'
main :: IO ()
main = do
    line <- getLine
    putStrLn $ show $ calc $ reverse line
