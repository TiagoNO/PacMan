#!/bin/bash

otmPolicy=$1
agentPolicy=$2
executable=$3
map_dir=$4
map=$5
outFile="analyse_results.txt"

for learningRate in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
do
    for discountRate in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
    do
        iterations=$((1))
        echo $learningRate $discountRate
        while [ 1 ]
        do
            ./$executable $map_dir$map $learningRate $discountRate $iterations 
            diff $otmPolicy $agentPolicy > /dev/null 2>&1
            error=$?
            if [ $error -eq 0 ]
            then
                #echo "$otmPolicy and $agentPolicy) are the same file"
                echo $learningRate $discountRate $iterations "\n"
            elif [ $error -eq 1 ]
            then
                echo "$otmPolicy and $agentPolicy (i=$iterations,l_r=$learningRate,d_r=$discountRate) differ"
            elif [ $error -eq 2 ]
            then
                echo "something went wrong (File ($otmPolicy|$agentPolicy) exists?)"
            fi
        iterations=$((iterations + 50))
        done
    done
done