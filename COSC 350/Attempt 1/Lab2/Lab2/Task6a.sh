#!/bin/bash
#Ian Thomas
#COSC350
for ((i=1; i<=5; i++)); do
  for((j=1; j<=i; j++)); do
    printf "$i" #printf so we dont break lines
  done
  echo "" #to add a space
done
