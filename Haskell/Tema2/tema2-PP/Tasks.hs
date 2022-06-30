-- =============== DO NOT MODIFY ===================

{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}

-- ==================================================

module Tasks where

import Dataset
import Data.List
import Text.Printf
import Data.Array
import Text.Read (readMaybe)


type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]
type ColumnName = String

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
            map (foldr (++) [] . intersperse ",")


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

{-
    TASK SET 2
-}

-- Task 1

getIndex :: ColumnName -> Row -> Int -> Int -> Int
getIndex col row len acc
    | acc >= len = -1
    | col == head row = acc
    | otherwise = getIndex col (tail row) len (acc + 1)

sortByColumn :: ColumnName -> Table -> Int -> Table
sortByColumn column table i = if i == -1 then table else stringOrInt column table i

stringOrInt :: ColumnName -> Table -> Int -> Table
stringOrInt column table i = if (readMaybe (head (tail table) !! i)::Maybe Float) == Nothing
                             then sortString column table i else sortInt column table i

sortString :: ColumnName -> Table -> Int -> Table
sortString column table i = sortBy (\e1 e2 -> if  (e1!!i) == (e2!!i) then compare (head e1) (head e2) else LT) sortedTable where
    sortedTable = sortBy (\e1 e2 -> compare (e1!!i) (e2!!i)) (tail table)

sortInt :: ColumnName -> Table -> Int -> Table
sortInt column table i = sortBy (\e1 e2 -> if (read (e1!!i)::Float) == (read (e2!!i)::Float)
                                           then compare (head e1) (head e2) else LT) sortedTable where
    sortedTable = sortBy (\e1 e2 -> compare (read (e1!!i)::Float) (read (e2!!i)::Float)) (tail table)

tsort :: ColumnName -> Table -> Table
tsort column table = head table:sortByColumn column table i where
    i = getIndex column (head table) (length (head table)) 0


-- Task 2

vunion :: Table -> Table -> Table
vunion t1 t2
    | head t1 /= head t2 = t1
    | otherwise  = t1 ++ tail t2

-- Task 3
addRows :: Table -> Int -> Row -> Table
addRows t n r
    | n == 0 = t
    | otherwise = addRows (t ++ [r]) (n-1) r

makeRow :: Int -> Row -> Row
makeRow n acc
    | n == 0 = acc
    | otherwise = makeRow (n-1) (acc ++ [""])

extendTable :: Table -> Table -> Table
extendTable small big = addRows small (length big - length small) (makeRow (length (head small)) [])

hunion :: Table -> Table -> Table
hunion t1 t2
    | length t1 > length t2 =  zipWith (++) t1 (extendTable t2 t1)
    | length t1 < length t2 = zipWith (++) (extendTable t1 t2) t2
    | otherwise = zipWith (++) t1 t2

-- Task 4

getCommonCols :: Row -> Row -> Row -> Row
getCommonCols (x:xs) ys acc
  | null xs && x `elem` ys = acc++[x]
  | null xs && x `notElem` ys = acc
  | x `elem` ys = getCommonCols xs ys (acc++[x])
  | x `notElem` ys = getCommonCols xs ys acc
getCommonCols xs ys acc = acc

checkElemInTable :: Value -> Table -> Bool
checkElemInTable v t = True `elem` (map (v `elem`) t)

addRemainingCols :: Row -> Table -> Row -> Row
addRemainingCols commonCols t res
  | null (head t) = res
  | head (head  t) `notElem` commonCols = addRemainingCols commonCols (map tail t) (res ++ [head(head(tail t))])
  | otherwise = addRemainingCols commonCols (map tail t) res

joinRows :: Table -> Table -> Row -> Row -> Row
joinRows t1 t2 commonCols acc
  | null (head t1) =  addRemainingCols commonCols t2 acc
  | head (head t1) `elem` commonCols = joinRows (map tail t1) t2 commonCols (acc ++ 
                                       [head (tail t2) !! getIndex (head (head t1)) (head t2) (length (head t2)) 0])
  | otherwise = joinRows (map tail t1) t2  commonCols (acc ++ [head(head(tail t1))])

getRow :: Table -> Value -> Row
getRow t v
  | null t = []
  | v `elem` head t = head t
  | otherwise = getRow (tail t) v

joinTables :: Int -> Table -> Table -> Row -> Table -> Table
joinTables index t1 t2 commonCols acc
  | null (tail t1) = acc
  | checkElemInTable (head (tail t1) !! index) t2 = joinTables index (head t1:tail(tail t1)) t2 commonCols (acc ++
                                                    [joinRows [head t1, head(tail t1)] [head t2, getRow (tail t2) (head (tail t1) !! index)] commonCols []])
  | otherwise = joinTables index (head t1:tail(tail t1)) t2 commonCols acc

tjoin :: ColumnName -> Table -> Table -> Table
tjoin key_column t1 t2
  | notElem key_column (head t1) || notElem key_column (head t2) = t1
  | otherwise = nub (head(zipWith (++) [head t1] [head t2])):joinTables index t1 t2 (getCommonCols (head t1) (head t2) []) [] where
    index = getIndex key_column (head t1) (length (head t1)) 0



-- Task 5

cartesian :: (Row -> Row -> Row) -> [ColumnName] -> Table -> Table -> Table
cartesian new_row_function new_column_names t1 t2 = new_column_names: cartesian2 new_row_function (tail t1) (tail t2)

cartesian2 :: (Row -> Row -> Row) -> Table -> Table -> Table
cartesian2 new_row_function  t1 t2
  | null t1 = []
  | otherwise = map (new_row_function (head t1)) t2 ++ cartesian2 new_row_function (tail t1) t2



-- Task 6

projection :: [ColumnName] -> Table -> Table
projection columns_to_extract t = transpose (extractColumns columns_to_extract t [])

extractColumns :: [ColumnName] -> Table -> Table -> Table
extractColumns columns_to_extract t acc
  | null columns_to_extract = acc
  | otherwise = extractColumns (tail columns_to_extract) t (acc ++ 
                [columnAsList (getIndex (head columns_to_extract) (head t) (length (head t)) 0) t []])

columnAsList :: Int -> Table -> Row -> Row
columnAsList i t acc
  | null t = acc
  | otherwise = columnAsList i (tail t) (acc ++ [head t !! i])

-- Task 7

filterTable :: (Value -> Bool) -> ColumnName -> Table -> Table
filterTable condition key_column t =  head t : filterTable2 condition key_column t

filterTable2 :: (Value -> Bool) -> ColumnName -> Table -> Table
filterTable2 condition key_column t
  | null (tail t) = []
  | condition (head (tail t) !! index) = head (tail t):filterTable2 condition key_column (head t:tail(tail t))
  | otherwise = filterTable2 condition key_column (head t:tail(tail t)) where
    index = getIndex key_column (head t) (length (head t)) 0