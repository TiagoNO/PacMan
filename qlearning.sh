#!/bin/bash
#echo "Map: $1"
#echo "Learning rate: $2"
#echo "Discount rate: $3"
#echo "Iterations: $4"
#echo "Agent: Q"
#cd source/
#g++ -o ../qlearning Simulador.cpp DataReader.cpp DataReader.h Agent.cpp Agent.h Environment.cpp Environment.h ApproxAgent.h ApproxAgent.cpp Features.h Features.cpp
#chmod +x ../qlearning
#cd ..
./qlearning $1 $2 $3 $4 "Q"
#sleep 15
