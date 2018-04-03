#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <set>
#include "Environment.h"

#define acima 0
#define abaixo 1
#define esquerda 2
#define direita 3

Environment::Environment(char **argv){
    this->data = Data(argv); // Initialize Data (defined in DataReader.h and DataReader.c)
    this->agent = QLearningAgent(this->data.getWidth(),this->data.getHeight()); //Initialize Agent (defined in Agent.c and Agent.h)

    srand(time(NULL));  // initialize seed

    this->map = this->data.getMap(); // get a copy of the map
    SetRandomPosition(this->data.getWidth(),this->data.getHeight()); // set the agent in a valid random position in the map
}
        
void Environment::SetRandomPosition(int n_size,int m_size){
    set<pair<int,int> > Validpositions;
    for(int i = 0; i < this->data.getWidth(); i++){
        for(int j = 0; j < this->data.getHeight(); j++){
            if(this->map[i][j] == '-'){
                Validpositions.insert(make_pair(i,j));  // search for all valid positions in the map and add them to an set os positions
            }
        }
    }

    int index = rand()%Validpositions.size();
    set<pair<int,int> >::const_iterator newPosition; // select a random position in the set of valid positions
    newPosition = Validpositions.begin();
    advance(newPosition,index);

    this->state.first = newPosition->first; // set the new state where the agent will start
    this->state.second = newPosition->second;
}

pair<int,int> Environment::getNextState(int action){
    if(action == acima){
        if(this->map[this->state.first - 1][this->state.second] == '*'){ // if its a wall, we stay where we are
            return this->state;
        }
        return make_pair(this->state.first - 1,this->state.second);
    }
    else if(action == abaixo){
        if(this->map[this->state.first + 1][this->state.second] == '*'){
            return this->state;
        }
        return make_pair(this->state.first + 1,this->state.second);        
    }
    else if(action == esquerda){
        if(this->map[this->state.first][this->state.second - 1] == '*'){
            return this->state;
        }
        return make_pair(this->state.first,this->state.second - 1); // set the new state based in the action given 
    }
    else if(action == direita){
        if(this->map[this->state.first][this->state.second + 1] == '*'){
            return this->state;
        }
        return make_pair(this->state.first,this->state.second + 1);        
    }
}

void Environment::UpdateState(){
    for(int i = 0; i < this->data.getNumIterations(); i++){
        printf("Iteration: %i\n",i);
        set<int> validActions = this->getValidActions(this->state); // get all valid actions given the current state of the agent
        int action_taken = this->agent.getAction(validActions,this->state); // get the action that the agent took (defined in Agent.c and Agent.h)

        pair<int,int> nextState = this->getNextState(action_taken); // get the next state given the action of the agent        
        set<int> nextValidActions = this->getValidActions(nextState); // get all the valid actions in the next state
        int maxValueNextState = this->agent.getBestQValue(nextValidActions,nextState); // get the max value of the next state

        this->agent.Update(this->state,nextState,action_taken,this->getReward(nextState),maxValueNextState,this->data.getDiscount(),this->data.getLearning_rate());
                        // call this fuction so the agent could  update the Q() function based in the reward (defined in Agent.c and Agent.h)
    }
    this->data.WriteQValues(this->agent.getQValues());
    this->data.WritePolicy(this->agent.getQValues());
}

int Environment::getReward(pair<int,int> state){
    if(map[state.first][state.second] == '-'){ // an empty space, that fine, keep moving!
        return -1;
    }
    else if(map[state.first][state.second] == '0'){ // found the prize! yammy!
        return 10;
        SetRandomPosition(this->data.getWidth(),this->data.getHeight()); // reset the position in a random place
    }
    else if(map[state.first][state.second] == '&'){ // oh no! Call the ghostbusters! We found a ghost!
        return -10;
        SetRandomPosition(this->data.getWidth(),this->data.getHeight()); // reset the position in a random place
    }
}

int Environment::getStateX(){
    return this->state.first;
}

int Environment::getStateY(){
    return this->state.second;
}

set<int> Environment::getValidActions(pair<int,int> state){
    set<int> actions;
    if(state.first - 1 >= 0){ // se é possivel ir para cima
        actions.insert(acima);
    }
    if(state.first + 1 < this->data.getWidth()){
        actions.insert(abaixo);
    }
    if(state.second - 1 >= 0){
        actions.insert(esquerda);
    }
    if(state.second + 1 < this->data.getHeight()){
        actions.insert(direita);
    }
    return actions;
}