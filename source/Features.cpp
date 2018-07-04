#include "Features.h"
#include <stdio.h>
#include <stdlib.h>

Features::Features(){
    this->features.insert(make_pair("bias",1.0));
    this->features.insert(make_pair("food-distance",0.0));
//    printf("feature[%s] = %f\n","bias",features["bias"]);
}

Features::Features(char **map,int map_width,int map_height){
    this->map = map;
    this->map = (char**)malloc(map_height*sizeof(char *));
    for(int i = 0; i < map_width; i++){
        this->map[i] = (char*)malloc(map_width*sizeof(char));
        for(int j = 0; j < map_width; j++){
            this->map[i][j] = map[i][j];
        }
    }
    this->map_w = map_width;
    this->map_h = map_height;
}

int Features::getGhostsOneStepAway(pair<int,int> state){
    int result = 0;
    if(state.first-1 >= 0){
        if(this->map[state.first-1][state.second] == '&'){
            result++;
        }        
    }
    if(state.first+1 >= 0){
        if(this->map[state.first+1][state.second] == '&'){
            result++;
        }        
    }
    if(state.second-1 >= 0){
        if(this->map[state.first][state.second-1] == '&'){
            result++;
        }        
    }
    if(state.second+1 >= 0){
        if(this->map[state.first][state.second+1] == '&'){
            result++;
        }        
    }
    return result;
}

int Features::add_valid_neighbors(std::list<pair<pair<int,int>,int> > *frontier,std::set<pair<int,int> > explored,std::pair<pair<int,int>,int> state){
    int result = 0;
    int x = state.first.first;
    int y = state.first.second;
    int cost = state.second + 1;
//   printf("state(search): (%i,%i,%i)\n",state.first.first,state.first.second,state.second);

    if(state.first.first >= 0 && state.first.first < this->map_h && state.first.second >= 0 && state.first.second < this->map_w){
//        printf("last state: (%i,%i)\n",state.first.first,state.first.second);
        std::pair<pair<int,int>,int> newState = make_pair(make_pair(x-1,y),cost);
        if (explored.find(newState.first) == explored.end() && state.first.first - 1 >= 0){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
//                printf("new state: (%i,%i)\n",newState.first.first,newState.first.second);
                frontier->push_back(newState);
            }
        }
        newState = make_pair(make_pair(x+1,y),cost);
        if (explored.find(newState.first) == explored.end() && state.first.first + 1 < this->map_h){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
//                printf("new state: (%i,%i)\n",newState.first.first,newState.first.second);
                frontier->push_back(newState);
            }
        }
        newState = make_pair(make_pair(x,y-1),cost);
        if (explored.find(newState.first) == explored.end() && state.first.second - 1 >= 0){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
//                printf("new state: (%i,%i)\n",newState.first.first,newState.first.second);
                frontier->push_back(newState);
            }
        }
        newState = make_pair(make_pair(x,y+1),cost);
        if (explored.find(newState.first) == explored.end() && state.first.second + 1 < this->map_w){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
//                printf("new state: (%i,%i)\n",newState.first.first,newState.first.second);
                frontier->push_back(newState);
            }
        }
    }
}

bool Features::isValid(pair<int,int> initial_state){
    if(initial_state.first >= 0 && initial_state.first < this->map_h){
        if(initial_state.second >= 0 && initial_state.second < this->map_w){
            return true;
        }
    }
    return true;
}

bool Features::is_goal(pair<int,int> state){
    if(this->map[state.first][state.second] == '0'){
//        printf("(%i,%i) = %c\n",state.first,state.second,this->map[state.first][state.second]);
        return true;
    }
//    printf("(%i,%i) = %c\n",state.first,state.second,this->map[state.first][state.second]);
    return false;
}

float Features::closestFood(pair<int,int> initial_state){
    std::list<pair<pair<int,int>,int> > frontier;
    std::set<pair<int,int> > explored;
    std::pair<pair<int,int>,int> state;
    frontier.push_front(make_pair(initial_state,0));
    
    while(frontier.size() > 0){
        state = frontier.front();
//        printf("State(search): (%i,%i,%i)\n",state.first.first,state.first.second,state.second);
        frontier.pop_front();
        if(explored.find(state.first) != explored.end()){
            continue;
        }
        explored.insert(state.first);
        if(is_goal(state.first)){
        //    printf("%i,%i",state.first.first,state.first.second);
            return float(state.second - 1);
        }
        add_valid_neighbors(&frontier,explored,state);
    }
    return 0.0;
}

pair<int,int> Features::calculateNextState(pair<int,int> initial_state,int action){
    pair<int,int> nextState = initial_state;
    if (action == acima){
        nextState.first -= 1;
    }
    if (action == abaixo){
        nextState.first += 1;
    }
    if (action == direita){
        nextState.second += 1;
    }
    if (action == esquerda){
        nextState.second -= 1;
    }
    return nextState;
}

float Features::enemyNearby(pair<int,int> nextState){
    if(this->map[nextState.first][nextState.second] == '&'){
        return 1.0;
    }
    else{
        return 0.0;
    }
}

void Features::getFeatures(pair<int,int> initial_state,int action){
        pair<int,int> nextState = calculateNextState(initial_state,action);
        this->features["bias"] = 1.0/10;
        this->features["food-distance"] = closestFood(nextState);
        this->features["food-distance"] /= (this->map_h*this->map_w);
        this->features["enemy-nearby"] = enemyNearby(nextState);
//        for(std::map<string,float>::const_iterator a = this->features.begin(); a != this->features.end(); a ++){
//            printf("feature[%s] = %f\n",a->first.c_str(),a->second);
//        }
}

std::set<string> Features::getFeaturesKeys(){
    std::set<string> features_keys;
    for(std::map<string,float>::const_iterator i = this->features.begin(); i != this->features.end(); i++){
        features_keys.insert(i->first);
    }
    return features_keys;
}