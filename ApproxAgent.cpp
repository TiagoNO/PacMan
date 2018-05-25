#include "ApproxAgent.h"

ApproximateAgent::ApproximateAgent(){
    this->feature = new Features();
}

ApproximateAgent::ApproximateAgent(int map_width,int map_height,Features *features):QLearningAgent(map_width,map_height){
    this->feature = features;
}