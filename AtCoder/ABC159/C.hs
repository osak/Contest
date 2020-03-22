{-# LANGUAGE OverloadedStrings #-} 
import qualified Data.Text as T
import qualified Data.Text.IO as I
import Text.Printf

main :: IO ()
main = do
    line <- I.getLine
    let n = read $ T.unpack line
    let len = (fromIntegral n) / 3
    printf "%.10f\n" (len**3 :: Double)