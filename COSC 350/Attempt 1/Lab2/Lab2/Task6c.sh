#!/bin/sh
#Ian Thomas
#COSC350
isvalid=0

echo "Enter number between 5 and 9"

while [ $isvalid -ne 1 ]
do
  read input #global

  if (( input < 5 || input > 9 )); then
    echo "Err: Input not between 5 and 9, try again"
  else
    isvalid=1
  fi
done

for (( i=0; i<=$input; i++ ))
do
  #get the number of spaces we need
  spacesneeded=$(( 9-$i ))
  for (( j=0; j<$spacesneeded; j++ ))
  do
    #print spaces
    printf " "
  done
  for (( j=0; j<$i; j++ ))
  do
    #then number
    printf "$i "
  done
  echo
done

exit 0
