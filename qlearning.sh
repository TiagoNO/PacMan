echo "Map: $1"
echo "Learning rate: $2"
echo "Discount rate: $3"
echo "Iterations: $4"
g++ -o qlearning Simulador.c Environment.c Environment.h DataReader.c DataReader.h Agent.c Agent.h
./qlearning $1 $2 $3 $4