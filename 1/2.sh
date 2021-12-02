#!/bin/sh

inputFile="input.txt"
previousMeasurement0=$(head -1 $inputFile)
previousMeasurement1=$(head -2 $inputFile | tail -1)
previousMeasurement2=$(head -3 $inputFile | tail -1)
previousSum=$(($previousMeasurement0+$previousMeasurement1+$previousMeasurement2))
increaseCounter=0
for line in $(tail -n +4 $inputFile)
do
    previousMeasurement0=$previousMeasurement1
    previousMeasurement1=$previousMeasurement2
    previousMeasurement2=$line
    sum=$(($previousMeasurement0+$previousMeasurement1+$previousMeasurement2))
    if [ $sum -gt $previousSum ]; then
        increaseCounter=$(($increaseCounter+1))
    fi
    previousSum=$sum
done
echo $increaseCounter