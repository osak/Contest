import Data.List

workdays :: [String]
workdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday"]

main :: IO ()
main = do
    line <- getLine
    let remain = case elemIndex line workdays of
               Just idx -> 5 - idx
               Nothing -> 0
    putStrLn $ show remain
