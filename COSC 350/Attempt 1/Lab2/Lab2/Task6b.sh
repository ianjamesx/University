#!/bin/sh
#Ian Thomas
#COSC350
for (( i=1; i<5; i++ ))
do
  for (( j=1; j<=$i; j++ ))
  do
    printf "*"
  done
  echo '' #break line
done

for (( i=4; i>=0; i-- ))
do
  for (( j=0; j<=$i; j++ ))
  do
    printf "*"
  done
  echo ''
done

exit 0
