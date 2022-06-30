-- =============== DO NOT MODIFY ===================

{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}

-- ==================================================

module Tasks where

import Dataset
import Data.List
import Text.Printf
import Data.Array

type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]


-- Prerequisities
split_by :: Char -> String -> [String]
split_by x = foldr op [""]
  where op char acc
            | char == x = "":acc
            | otherwise = (char:head acc):tail acc

read_csv :: CSV -> Table
read_csv = map (split_by ',') . split_by '\n'

write_csv :: Table -> CSV
write_csv = intercalate "\n" .
            map (intercalate ",")


{-
    TASK SET 1
-}


-- Task 1
floatList :: Row -> [Float]
floatList = map (read::String->Float)

sumOfPerson :: Row -> Float
sumOfPerson l = sum (floatList (tail l))

averageSteps :: Row -> Row
averageSteps l = head l:[printf "%.2f" x] where
  x =  sumOfPerson l / 8

compute_average_steps :: Table -> Table
compute_average_steps m = ["Name", "Average Number of Steps"]:map averageSteps (tail m)


-- Task 2

-- Number of people who have achieved their opal:
pplAchived :: Row -> Bool
pplAchived l
  | sumOfPerson l >= 1000 = True
  | otherwise = False


get_passed_people_num :: Table -> Int
get_passed_people_num m
    | null m = 0
    | pplAchived (head m) = 1 + get_passed_people_num (tail m)
    | otherwise  = get_passed_people_num (tail m)


-- Percentage of people who have achieved their:

get_passed_people_percentage :: Table -> Float
get_passed_people_percentage m = fromIntegral (get_passed_people_num m) / fromIntegral (length m)


-- Average number of daily steps
get_steps_avg :: Table -> Float
get_steps_avg m = sum (map sumOfPerson (tail m)) / (fromIntegral (length m) - 1)


-- Task 3
stringList :: [Float] -> Row
stringList = map (printf "%.2f"::Float->String)

get_avg_steps_per_h :: Table -> Table
get_avg_steps_per_h m = [["H10","H11","H12","H13","H14","H15","H16","H17"], 
                        stringList (map (/ fromIntegral (length m - 1)) (foldl1 (zipWith (+)) x))] where
  x = map (floatList . tail) (tail m)


-- Task 4
intList :: Row -> [Int]
intList = map (read::String->Int)

stringList2 :: [Int] -> Row
stringList2 = map (printf "%d"::Int->String)

makeTable :: [[Int]] -> Table
makeTable x = ["VeryActiveMinutes":stringList2 (op (map head x) [0,0,0]),  
              "FairlyActiveMinutes":stringList2 (op (map (head.tail) x)  [0,0,0]), 
              "LightlyActiveMinutes":stringList2 (op (map (head.tail.tail) x)  [0,0,0])] where
  op [] acc = acc
  op (l:ls) acc
    | l < 50 = op ls ((head acc + 1):tail acc)
    | l < 100 = op ls (head acc:(acc!!1 + 1):tail (tail acc))
    | otherwise = op ls [head acc, acc!!1 , acc!!2 + 1]


get_activ_summary :: Table -> Table
get_activ_summary m = ["column","range1","range2","range3"]:makeTable x where
  x = map (intList . (tail . tail) . tail) (tail m)


-- Task 5
get_ranking :: Table -> Table
get_ranking m = map  (take 2) x where
  x = ["Name","Total Steps"]:sortBy (\e1 e2 -> compare (read (e1!!1)::Int) (read (e2!!1)::Int)) (tail m)


-- Task 6

sumFourElems :: [Int] -> Int
sumFourElems = op 0 where
    op counter  _
      | counter == 4 = 0
    op counter [] = 0
    op counter (x:xs) = x + op (counter + 1) xs

createTable :: Row -> Row
createTable l = [head l, x , y, printf "%.2f" (abs ((read::String->Float) x - (read::String->Float) y))] where
  x = (printf "%.2f" . (/4.0) . (fromIntegral::Int->Float) . sumFourElems . intList) (tail l)
  y = (printf "%.2f" . (/4.0) . (fromIntegral::Int->Float) . sumFourElems . intList) ((tail.tail.tail.tail.tail) l)

get_steps_diff_table :: Table -> Table
get_steps_diff_table m = ["Name","Average first 4h","Average last 4h","Difference"]:sortBy (\e1 e2 -> compare (read (e1!!3)::Float) (read (e2!!3)::Float))
                         (map createTable (tail m))


-- Task 7

-- Applies the given function to all the values
vmap :: (Value -> Value) -> Table -> Table
vmap f = map (map f)


-- Task 8

-- Applies the given function to all the entries
rmap :: (Row -> Row) -> [String] -> Table -> Table
rmap f s m = s:map f m


get_sleep_total :: Row -> Row
get_sleep_total r = [head r, printf "%.2f" (sumOfPerson r)]
