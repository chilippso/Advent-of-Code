#!/bin/sh

inputFile="input.txt"
previousMeasurement=$(head -1 $inputFile)
increaseCounter=0
for line in $(tail -n +2 $inputFile)
do
    if [ $line -gt $previousMeasurement ]; then
        increaseCounter=$(($increaseCounter+1))
    fi
    previousMeasurement=$line
done
echo $increaseCounter