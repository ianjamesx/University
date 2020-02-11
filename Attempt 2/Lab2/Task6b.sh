#!/bin/sh
#Ian Thomas
#COSC350

for i in $(seq 1 5)
do
  for j in $(seq 1 $i)
  do
    printf "*"
  done
  echo '' #break line
done

for i in $(seq 4 -1 0) #decrement by -1
do
  for j in $(seq 1 $i)
  do
    printf "*"
  done
  echo ''
done

exit 0
