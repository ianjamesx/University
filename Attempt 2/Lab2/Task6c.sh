#!/bin/sh
#Ian Thomas
#COSC350
isvalid=0

echo "Enter number between 5 and 9"

while [ $isvalid -ne 1 ] #verify input loop
do
  read input #global

  if [ $input -lt 5 ] || [ $input -gt 9 ]
  then
    echo "Err: Input not between 5 and 9, try again"
  else
    isvalid=1
  fi
done

for i in $(seq 0 $input)
do
  #get the number of spaces we need
  spacesneeded=$(( 9-$i ))
  for j in $(seq 0 $spacesneeded)
  do
    #print spaces
    printf " "
  done
  for j in $(seq 0 $i)
  do
    #then number
    printf "$i "
  done
  echo
done

exit 0
