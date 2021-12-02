#!/bin/sh

inputFile="input.txt"
horizontalPosition=0
depth=0

while read line || [ -n "$line" ];
do
    direction=$(echo $line | cut -d " " -f 1)
    value=$(echo $line | cut -d " " -f 2)
    
    case "$direction" in
        "forward")
            horizontalPosition=$(($horizontalPosition + $value))
            ;;
        "down")
            depth=$(($depth + $value))
            ;;
        "up")
            depth=$(($depth - $value))
            ;;
        *)
            ;;
    esac
done < $inputFile
echo $(($horizontalPosition * $depth))