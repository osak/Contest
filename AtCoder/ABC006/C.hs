import Control.Applicative

calc :: Int -> Int -> (Int, Int, Int)
calc n m = let t = m - 2*n
               y = t `mod` 2
               z = (t - y) `div` 2
               x = n - y - z
           in if (all (>= 0) [x, y, z])
                then (x, y, z)
              else
                (-1, -1, -1)

main = do
  wd <- words <$> getLine
  let n:m:_ = map read wd
  let (x, y, z) = calc n m
  putStrLn ((show x) ++ " " ++ (show y) ++ " " ++ (show z))
