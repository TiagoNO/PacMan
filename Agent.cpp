#include "Agent.h"
#include <stdio.h>

#define acima 0
#define abaixo 1
#define esquerda 2
#define direita 3

QLearningAgent::QLearningAgent(){
}

QLearningAgent::QLearningAgent(int map_width,int map_height){
    this->Qvalue = (float ***)malloc(map_width*sizeof(float *));
    for(int i = 0; i < map_width; i++){
        this->Qvalue[i] = (float **)malloc(map_height*sizeof(float*));
        for(int j = 0; j < map_height; j++)
        {
            this->Qvalue[i][j] = (float *)malloc(4*sizeof(float));
            for(int k = 0; k < 4; k++){
                this->Qvalue[i][j][k] == 0;
            }
        }
    }
}
        
int QLearningAgent::getAction(set<int> validActions,pair<int,int> state){
    int max = -INT32_MAX;
    int best_action = -1;
    for(set<int>::const_iterator i = validActions.begin(); i != validActions.end(); i++){
        if(this->Qvalue[state.first][state.second][(*i)] > max){
            max = this->Qvalue[state.first][state.second][(*i)];
            best_action = (*i);
        }
    }
    printf("At state (%i,%i) the best action found was %i\n",state.first,state.second,best_action);
    return best_action;
}

float QLearningAgent::getBestQValue(set<int> validActions,pair<int,int> state){
    int max = -INT32_MAX;
    for(set<int>::const_iterator i = validActions.begin(); i != validActions.end(); i++){
        if(this->Qvalue[state.first][state.second][(*i)] > max){
            max = this->Qvalue[state.first][state.second][(*i)];
        }
    }
    printf("At state (%i,%i) the max Q value was %f\n",state.first,state.second,max);
    return max;
}

void QLearningAgent::Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate){
    this->Qvalue[state.first][state.second][action] += learning_rate*(reward + discount*NextQValue - this->Qvalue[state.first][state.second][action]);
    printf("Q[%i][%i][%i] = %f\n",state.first,state.second,action,this->Qvalue[state.first][state.second][action]);
}

float *** QLearningAgent::getQValues(){
    return this->Qvalue;
}