#include "Features.h"
#include <stdio.h>


Features::Features(){
    
}

Features::Features(char **map,int map_width,int map_height){
    this->map = map;
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

    if(state.first.first-1 >= 0){
        std::pair<pair<int,int>,int> newState = make_pair(make_pair(x-1,y),cost);
        if (explored.find(newState.first) == explored.end()){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
                frontier->push_back(newState);
            }
        }
    }
    if(state.first.first+1 >= 0){
        std::pair<pair<int,int>,int> newState = make_pair(make_pair(x+1,y),cost);
        if (explored.find(newState.first) == explored.end()){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
                frontier->push_back(newState);
            }
        }
    }
    if(state.first.second-1 >= 0){
        std::pair<pair<int,int>,int> newState = make_pair(make_pair(x,y-1),cost);
        if (explored.find(newState.first) == explored.end()){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
                frontier->push_back(newState);
            }
        }
    }
    if(state.first.second+1 >= 0){
        std::pair<pair<int,int>,int> newState = make_pair(make_pair(x,y+1),cost);
        if (explored.find(newState.first) == explored.end()){
            if(this->map[newState.first.first][newState.first.second] == '-' || this->map[newState.first.first][newState.first.second] == '0'){
                frontier->push_back(newState);
            }
        }
    }
}


int Features::closestFood(pair<int,int> initial_state){
    std::list<pair<pair<int,int>,int> > frontier;
    std::set<pair<int,int> > explored;
    std::pair<pair<int,int>,int> state;


    frontier.push_front(make_pair(initial_state,0));

    while(frontier.size() > 0){
        state = frontier.front();
        frontier.pop_front();
        if(explored.find(state.first) != explored.end()){
            continue;
        }
        explored.insert(state.first);
        if(this->map[state.first.first][state.first.second] == '0'){
//            printf("\n\n%i,%i\n\n",state.first.first,state.first.second);
            return state.second;
        }
        add_valid_neighbors(&frontier,explored,state);
/*        for(std::list<pair<pair<int,int>,int> >::const_iterator i = frontier.begin(); i != frontier.end(); i++){
            printf("(%i,%i,%i) ",i->first.first,i->first.second,i->second);
        }
        printf("\n");
*/    }
    return -1;
}

void Features::getFeatures(pair<int,int> initial_state){
        this->features["bias"] = 1.0;
        //this->features["#-of-ghosts-1-step-away"] = getGhostsOneStepAway(initial_state);
        int dist = closestFood(initial_state);
        if (dist != -1){
            printf("dist: %i\n",dist);
            this->features["food"] = dist;
        }
}

std::set<string> Features::getFeaturesKeys(){
    std::set<string> features_keys;
    for(std::map<string,float>::const_iterator i = this->features.begin(); i != this->features.end(); i++){
        features_keys.insert(i->first);
    }
    return features_keys;
}