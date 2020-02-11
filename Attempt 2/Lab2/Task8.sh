#!/bin/bash
#Ian Thomas
#COSC350
n=$1 #take first param

if [ $# -eq 0 ]
then
  echo "No parameters supplied, exiting"
  exit 1
fi

while [ $n -gt 0 ]
do
    remainder=$(( $n % 10 )) #get remainder (e.g. at this point, number at end)
    n=$(( $n / 10 )) #divide by 10 to cut off last number
    sum=$(( $sum + $remainder )) #sum

done

echo  "sum of digits: $sum"
