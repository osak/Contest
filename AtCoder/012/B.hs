import Data.Array
import Text.Printf

solve :: Int -> Double -> Double -> Double -> Double
solve n va vb l | n == 0 = l
                | otherwise = solve (n-1) va vb (vb * l / va)
main :: IO ()
main = do
    line <- getLine
    let arr = listArray (0,3) $ map (read::String->Int) $ words line :: Array Int Int
    printf "%.10f\n" $ solve (arr!0) (fromIntegral $ arr!1) (fromIntegral $ arr!2) (fromIntegral $ arr!3)
