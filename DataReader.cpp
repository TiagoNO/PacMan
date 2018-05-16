#include <iostream>
#include "DataReader.h"

#define acima 0
#define abaixo 1
#define esquerda 2
#define direita 3

#define max_float 214748


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
    }

    Data::Data(char **argv){
        // constructor
        this->dir = argv[1]; // first argument given in the main file is the directory/name of the file where is the map
        this->learning_rate = atof(argv[2]); // the second argument is the learning rate
        this->discount = atof(argv[3]); // the third argument is the discount
        this->num_iterations = atoi(argv[4]); // the forth argument is the number of iterations that the agent can do
        this->agent_type = argv[5];
        //this->log = fopen("data_log.txt","w");

        printf("Dir: %s\nLearning rate: %f\nDiscount: %f\nIterations: %i\n",this->dir,this->learning_rate,this->discount,this->num_iterations);
        this->setMap();
    }

    Data::Data(){

    }

    char* Data::getDir(){
        return this->dir;
    }

    char** Data::getMap(){
        return this->map;
    }

    float Data::getDiscount(){
        return this->discount;
    }

    float Data::getLearning_rate(){
        return this->learning_rate;
    }

    int Data::getWidth(){
        return this->n_size;
    }

    int Data::getHeight(){
        return this->m_size;
    }

    int Data::getNumIterations(){
        return this->num_iterations;
    }

    void Data::WriteQValues(float ***Qvalue){
        FILE *output;
        float ***Q = Qvalue;
        output = fopen("q.txt","w");
        for(int i = 0; i < this->n_size; i++){
            for(int j = 0; j < this->m_size; j++){
                fprintf(output,"%i,%i,direita,%f\n",i,j,Q[i][j][direita]);
                fprintf(output,"%i,%i,esquerda,%f\n",i,j,Q[i][j][esquerda]);
                fprintf(output,"%i,%i,acima,%f\n",i,j,Q[i][j][acima]);
                fprintf(output,"%i,%i,abaixo,%f\n",i,j,Q[i][j][abaixo]);
            }
        }
    }
    void Data::WritePolicy(float ***Qvalue){
        FILE *output;
        output = fopen("pi.txt","w");
        for(int i = 0; i < this->n_size; i++){
            for(int j = 0; j < this->m_size; j++){
                if(this->map[i][j] == '#'){
                    fprintf(output,"#");
                }
                else if(this->map[i][j] == '0'){
                    fprintf(output,"0");
                }
                else if(this->map[i][j] == '&'){
                    fprintf(output,"&");
                }
                else{
                    float max = -max_float;
                    int action = 0;
                    for(int k = 0; k < 4; k++){
                        if(Qvalue[i][j][k] > max){
                            max = Qvalue[i][j][k];
                            action = k;
                        }
                    }
                    if(action == acima){
                        fprintf(output,"^");
                    }
                    if(action == abaixo){
                        fprintf(output,"v");
                    }
                    if(action == direita){
                        fprintf(output,">");
                    }
                    if(action == esquerda){
                        fprintf(output,"<");
                    }
                }
        }
        fprintf(output,"\n");
    }
}
