#!/bin/bash

agentPolicy="pi.txt"
executable="qlearning.sh"
map_dir="maps/"
outFile="results_"
iter_jumps=$((100))

for map in "pacmaze-01-tiny.txt" "pacmaze-02-mid-sparse.txt" "pacmaze-03-tricky.txt"
do
    for learningRate in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
    do
        for discountRate in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
        do
            iterations=$((1))
            echo $learningRate $discountRate
            otmPolicy="pi_star_$map"
            while [ 1 ]
            do
                ./$executable $map_dir$map $learningRate $discountRate $iterations 
                diff $otmPolicy $agentPolicy > /dev/null 2>&1
                error=$?
                if [ $error -eq 0 ]
                then
                    #echo "$otmPolicy and $agentPolicy) are the same file"
                    echo $learningRate $discountRate $iterations >> $outFile$map 
                    break
                elif [ $error -eq 1 ]
                then
                    echo "$otmPolicy and $agentPolicy (i=$iterations,l_r=$learningRate,d_r=$discountRate) differ"
                elif [ $error -eq 2 ]
                then
                    echo "something went wrong (File ($otmPolicy|$agentPolicy) exists?)"
                fi
            iterations=$((iterations + iter_jumps))
            done
        done
    done
done