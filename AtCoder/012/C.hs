import Control.Monad
import Data.Array.IO
import Data.Array.IArray
import Debug.Trace

type IOField = IOArray (Int,Int) Char
type Field = Array (Int,Int) Char

countField :: Field -> (Int,Int)
countField field = foldl accum (0,0) [(r,c) | r <- [0..18], c <- [0..18]]
    where
        accum (on,xn) pos = 
            let ch = field!pos
            in if ch == 'o' then (on+1,xn)
                            else if ch == 'x' then (on,xn+1)
                                              else (on,xn)

checkWin :: Char -> Field -> Bool
checkWin color field = (checkWin' rowList) || 
                       (checkWin' colList) || 
                       (checkWin' diag1List) || 
                       (checkWin' diag2List)
    where
        checkWin' (l:ls) = 
            let seq = maximum $ scanl accum 0 l
                win = seq >= 5
            in if win then True
                      else checkWin' ls
        checkWin' _ = False
        accum cur pos = if field!pos == color then cur+1
                                              else 0
        rowList = [[(r,c) | c <- [0..18]] | r <- [0..18]]
        colList = [[(r,c) | r <- [0..18]] | c <- [0..18]]
        diag1List = [[(r,c) | r <- [0..18], c <- [0..18], r+c == s] | s <- [0..36]]
        diag2List = [[(r,c) | r <- [0..18], c <- [0..18], r-c == s] | s <- [-18..18]]

checkRemoved :: (Int,Int) -> Field -> Bool
checkRemoved pos field = 
    let newField = field // [(pos, '.')]
    in not $ checkWin (field!pos) newField

checkLastTurn :: Char -> Field -> Bool
checkLastTurn turn field = or $ map checkAt [(r,c) | r <- [0..18], c <- [0..18]]
    where
        checkAt pos =
            let ch = field!pos
            in if ch == turn then checkRemoved pos field
                             else False

isValid :: Field -> Bool
isValid field = let (on,xn) = countField field
                in if on < xn || on >= xn+2
                      then False
                      else let turn = if on == xn
                                         then 'x'
                                         else 'o'
                           in (on+xn == 0) || (notWin (opposite turn) field && checkLastTurn turn field)
    where
        notWin color field = not $ checkWin color field
        opposite 'x' = 'o'
        opposite 'o' = 'x'

main :: IO ()
main = do
    field <- newArray ((0,0),(18,18)) '.' :: IO IOField
    forM_ [0..18] $ \r -> do
        forM_ [0..18] $ \c -> do
            ch <- getChar
            writeArray field (r,c) ch
        getChar
    f <- freeze field
    putStrLn $ if isValid f
                  then "YES"
                  else "NO"
