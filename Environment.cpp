#include <string>
#include <stdlib.h>
#include <time.h>
#include <set>
#include "Environment.h"

using namespace std;


Environment::Environment(int n_size,int m_size,char **map){
    srand(time(NULL));
    this->map = map;
    this->n_size = n_size;
    this->m_size = m_size;
}
        
void Environment::ResetPosition(int n_size,int m_size){

}

int Environment::getReward(){
    if(map[this->state_x][this->state_y] == '-'){
        return -1;
    }
    else if(map[this->state_x][this->state_y] == '0'){
        return 10;
    }
    else if(map[this->state_x][this->state_y] == '&'){
        return -10;
    }
}

int Environment::getStateX(){
    return this->state_x; 
}

int Environment::getStateY(){
    return this->state_y;
}

set<string> Environment::getValidActions(){
    set<string> actions;
    if(this->state_x - 1 >= 0){ // se é possivel ir para cima
        actions.insert("acima");
    }
    if(this->state_x + 1 < this->n_size){
        actions.insert("abaixo");
    }
    if(this->state_y - 1 >= 0){
        actions.insert("esquerda");
    }
    if(this->state_y + 1 < this->m_size){
        actions.insert("direita");
    }
    return actions;
}