#!/bin/sh
#Ian Thomas
#COSC350
n=$1 #take first param
fact=1

if [ $# -eq 0 ]
then
  echo "No parameters supplied, exiting"
  exit 1
fi

while(( $n>1))
do
  fact=$((fact * $n))
  n=$(($n - 1))
done

echo "Factorial: $fact"

exit 0;
