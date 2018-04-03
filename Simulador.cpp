#include <stdio.h>
#include <stdlib.h>
#include "Environment.h"


int main(int agrc,char *argv[]){
    Environment Simulator = Environment(argv);
    Simulator.UpdateState();
}