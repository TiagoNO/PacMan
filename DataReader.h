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
        int num_iterations; // the number os plays that the agent can do

    private:
        void setMap();
    
    public:
        Data();
        Data(char **argv);
        char* getDir();
        char** getMap();
        int getDiscount();
        int getLearning_rate();
        int getWidth();
        int getHeight();
        int getNumIterations();
        void WriteQValues(float ***QValue);
        void WritePolicy(float ***QValue);
        //TODO: function to write logs and results
};