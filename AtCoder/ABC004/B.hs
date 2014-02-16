import Control.Applicative

main = do
  あずにゃん <- lines <$> getContents
  putStrLn $ unlines $ reverse $ map reverse あずにゃん
