import Data.Sequence as Q

readInts :: IO [Int]
readInts = do
    line <- getLine
    return $ map read $ words line

solve2 t books = go 0 empty books
    where
    go sum buf [] = Q.length buf
    go sum buf rem@(b:bs) | sum+b <= t = go (sum+b) (b<|buf) bs
                          | otherwise = case viewr buf of
                                          EmptyR -> go sum buf bs
                                          s :> r -> max (Q.length buf) $ go (sum-r) s rem
main :: IO ()
main = do
    a <- readInts
    books <- readInts
    let (n, t) = (a!!0, a!!1)
    putStrLn $ show $ solve2 t books
