#!/bin/bash
#Ian Thomas
#COSC350
echo "Enter the name of a directory to search"
read dir

#check if ~ is first char

firstchar = ${dir:0:1}
echo $firstchar

if [ -d $dir ]; then
  echo "directory found"
else
  echo "Err: directory not found, exiting"
  exit 1
fi

cd $dir

attempts=0
echo "Enter name of text file"

while [ $attempts -lt 3 ]
do
  read file
  if [ -e $file ];
  then
    echo "File found"
    break
  else
    attempts=$(( attempts+1 ))
    if [ $attempts -eq 3 ]; then
      echo "File not found, all attempts (3 / 3) used, exiting"
      exit 2
    else
      echo "File not found, please try again ($attempts / 3 attempts used)"
    fi
  fi
done

echo "Enter a word to search for in $file"
read word


if grep -q $word $file; then
  echo "$word FOUND!"
else
  echo "$word NOT FOUND"
fi

exit 0
