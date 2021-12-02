#!/bin/sh

inputFile="input.txt"
horizontalPosition=0
depth=0
aim=0

while read line || [ -n "$line" ];
do
    direction=$(echo $line | cut -d " " -f 1)
    value=$(echo $line | cut -d " " -f 2)
    
    case "$direction" in
        "forward")
            horizontalPosition=$(($horizontalPosition + $value))
            depth=$((depth + ($aim * $value)))
            ;;
        "down")
            aim=$(($aim + $value))
            ;;
        "up")
            aim=$(($aim - $value))
            ;;
        *)
            ;;
    esac
done < $inputFile
echo $(($horizontalPosition * $depth))