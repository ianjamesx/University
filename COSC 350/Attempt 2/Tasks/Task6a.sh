#!/bin/bash
#Ian Thomas
#COSC350
for i in $(seq 1 5)
do
  for j in $(seq 1 $i)
  do
    printf "$i" #printf so we dont break lines
  done
  echo "" #to add a space
done
