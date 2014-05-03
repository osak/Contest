{-# LANGUAGE BangPatterns #-}
import Control.Monad
import Control.Applicative
import Data.Maybe
import Data.Array.IO
import qualified Data.ByteString.Char8 as BS

type Node = [Int]
type Graph = IOArray Int Node
type Memo = IOUArray Int Bool

data Queue = Queue ([Int], [Int])

newQueue :: Queue
newQueue = Queue ([], [])

newQueueWith :: [Int] -> Queue
newQueueWith inL = Queue (inL, [])

pushQueue :: Queue -> Int -> Queue
pushQueue (Queue (inL, outL)) val = Queue (val:inL, outL)

popQueue :: Queue -> (Int, Queue)
popQueue (Queue ([], [])) = error "Queue is empty"
popQueue (Queue (inL, [])) = popQueue (Queue ([], reverse inL))
popQueue (Queue (inL, o:os)) = (o, Queue (inL, os))

isEmpty :: Queue -> Bool
isEmpty (Queue ([], [])) = True
isEmpty _ = False

readIntLine :: IO [Int]
readIntLine = map (fst . fromJust . BS.readInt) <$> (BS.words <$> BS.getLine)

readGraph :: Int -> IO Graph
readGraph m = do
  graph <- newArray (1, m+1) []
  edges <- readEdges
  forM_ edges $ \(a,b) -> do
    addEdge graph a b
    addEdge graph b a
  return graph
  where
    readEdges = map (\(a:b:_) -> (a,b)) <$> replicateM m readIntLine
    addEdge :: Graph -> Int -> Int -> IO ()
    addEdge graph from to = do
      cur <- readArray graph from
      writeArray graph from (to:cur)

bfs :: Graph -> Memo -> Queue -> IO [Int]
bfs graph memo q
  | isEmpty q = return []
  | otherwise = do
      let (v, nq) = popQueue q
      writeArray memo v True
      next <- children v
      let nq' = foldl pushQueue nq next
      (liftM (v:)) $ bfs graph memo nq'
        where
          children v = do
            vs <- readArray graph v
            filterM (\child -> (liftM not) $ readArray memo child) vs

main :: IO ()
main = do
  n <- read <$> getLine
  graph <- readGraph (n-1)
  memo <- newArray (1, n) False
  l1 <- last <$> bfs graph memo (newQueueWith [1])
  memo <- newArray (1, n) False
  l2 <- last <$> bfs graph memo (newQueueWith [l1])
  putStrLn ((show l1) ++ " " ++ (show l2))
