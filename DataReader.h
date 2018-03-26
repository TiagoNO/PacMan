#include <iostream>
#include <stdio.h>
using namespace std;

class Data{

    private: 
        char* dir; // directory of the info we need
        char** map; // the map where the agent will act
        int learning_rate; // learning rate
        int discount; // discount rate
        int n_size; // width of the map
        int m_size; // height of the map
        int num_iteractions; // the number os plays that the agent can do

    private:
        void setMap();
    
    public:
        Data(char **argv);
        char* getDir();
        char** getMap();
        int getDiscount();
        int getLearning_rate();
};