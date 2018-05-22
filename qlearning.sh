#!/bin/bash
echo "Map: $1"
echo "Learning rate: $2"
echo "Discount rate: $3"
echo "Iterations: $4"
echo "Agent: $5"
FILE=qlearning
DIR="${PWD}"
#if test -f "$DIR/$FILE";
#then
    #Programa já compilado, apenas precisa ser executado
#    echo "Already was built, lets roll!"
#else
 #   #Programa não foi compilado, vamos compila-lo
#    echo "Program wasn't built, get the bricks!"
#    chmod +x Compilar.sh
#    ./Compilar.sh
#    echo "Finished compilation, lets get started!"
#fi

#g++ -o qlearning Simulador.cpp DataReader.cpp DataReader.h Agent.cpp Agent.h Environment.cpp Environment.h ApproxAgent.h ApproxAgent.cpp Features.h Features.cpp
#chmod +x qlearning
time ./qlearning $1 $2 $3 $4 $5
sleep 15
