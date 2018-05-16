#include "ApproxAgent.h"

ApproximateAgent::ApproximateAgent(){

}

ApproximateAgent::ApproximateAgent(int map_width,int map_height,Features *features):QLearningAgent(map_width,map_height){
    std::set<string> f = features->getFeaturesKeys();
    for(std::set<string>::const_iterator i = f.begin(); i != f.end(); i++){
        this->weights[(*i)] = 0.0;
    }
    this->feature = features;
}