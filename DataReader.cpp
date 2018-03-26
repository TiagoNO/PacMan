#include <iostream>
#include <stdio.h>
#include "DataReader.h"

using namespace std;

    void Data::setMap(){ // function that gets the map on the file
        FILE *arq;
        arq = fopen(this->dir,"r");
        if(arq == NULL){
            std::cout << "Error: File could not be opened" << endl;
            return;
        }

        fscanf(arq,"%i%i",&(this->n_size),&(this->m_size)); // read the size of the map

        this->map = (char**)malloc(this->n_size*sizeof(char *)); // initialize the matrix of the map
        for(int i = 0; i < this->n_size; i++){
            this->map[i] = (char *)malloc(this->m_size*sizeof(char));
        }

            std::cout << "The size of the map is " << this->n_size << "x" << this->m_size << "." << endl;
            for(int i = 0; i < this->n_size; i++){
                fscanf(arq,"%s",this->map[i]);
            }
            std::cout << this->map << endl;
        }

    Data::Data(char **argv){
        // constructor 
        this->dir = argv[1]; // first argument given in the main file is the directory/name of the file where is the map
        this->learning_rate = atoi(argv[2]); // the second argument is the learning rate
        this->discount = atoi(argv[3]); // the third argument is the discount
        this->num_iteractions = atoi(argv[4]); // the forth argument is the number of iterations that the agent can do
        this->setMap();
    }

    char* Data::getDir(){
        return this->dir;
    }

    char** Data::getMap(){
        return this->map;
    }

    int Data::getDiscount(){
        return this->discount;
    }

    int Data::getLearning_rate(){
        return this->learning_rate;
    }