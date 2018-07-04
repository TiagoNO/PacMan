#include "Agent.h"

#define acima 0
#define abaixo 1
#define esquerda 2
#define direita 3
#define max_float 214748

QLearningAgent::QLearningAgent(){
}

QLearningAgent::QLearningAgent(int map_width,int map_height){

    this->log = fopen("agent_log.txt","w");

    this->Qvalue = (float ***)malloc(map_width*sizeof(float **));
    for(int i = 0; i < map_width; i++){
        this->Qvalue[i] = (float **)malloc(map_height*sizeof(float*));
        for(int j = 0; j < map_height; j++)
        {
            this->Qvalue[i][j] = (float *)malloc(4*sizeof(float));
            for(int k = 0; k < 4; k++){
                this->Qvalue[i][j][k] = 0.0;
            }
        }
    }
}
        
int QLearningAgent::getAction(set<int> validActions,pair<int,int> state){
    float max = -max_float;
    int best_action = -1;
    for(set<int>::const_iterator i = validActions.begin(); i != validActions.end(); i++){
        if(this->Qvalue[state.first][state.second][(*i)] > max){
            max = this->Qvalue[state.first][state.second][(*i)];
            best_action = (*i);
        }
    }
//    printf("At state (%i,%i) the best action found was %i\n",state.first,state.second,best_action);
    fprintf(this->log,"At state (%i,%i) the best action found was %i",state.first,state.second,best_action);
    fprintf(this->log,"{%f,%f,%f,%f}\n",this->Qvalue[state.first][state.second][0],this->Qvalue[state.first][state.second][1],this->Qvalue[state.first][state.second][2]
    ,this->Qvalue[state.first][state.second][3]);
    return best_action;
}

float QLearningAgent::getBestQValue(set<int> validActions,pair<int,int> state){
    float max = -max_float;
    for(set<int>::const_iterator i = validActions.begin(); i != validActions.end(); i++){
        if(this->Qvalue[state.first][state.second][(*i)] > max){
            max = this->Qvalue[state.first][state.second][(*i)];
        }
    }
    fprintf(this->log,"At state (%i,%i) the max Q value was %f\n",state.first,state.second,max);
    return max;
}

float QLearningAgent::getQvalue(pair<int,int> state,int action){
    return this->Qvalue[state.first][state.second][action];
}


void QLearningAgent::Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate){
    this->Qvalue[state.first][state.second][action] += (float) learning_rate*(reward + discount*NextQValue - this->getQvalue(state,action));
    printf("Q[%i][%i][%i] = %f\n",state.first,state.second,action,this->Qvalue[state.first][state.second][action]);
    fprintf(this->log,"learning_r: %f,reward: %f,discount: %f,NextQValue: %f,Q[state] : %f\n",learning_rate,reward,discount,NextQValue,this->Qvalue[state.first][state.second][action]);
    fprintf(this->log,"Q[%i][%i][%i] = %f\n",state.first,state.second,action,this->Qvalue[state.first][state.second][action]);
}

float *** QLearningAgent::getQValues(){
    return this->Qvalue;
}