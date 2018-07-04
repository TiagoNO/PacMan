#include <time.h>
#include <stdlib.h>
#include "DataReader.h"
#include "ApproxAgent.h"

using namespace std;

class Environment{
    private:
        pair<int,int> state; // the position of the agent in the map
        char **map;  // matrix of chars that represent the map
        QLearningAgent *agent; // defined in Agent.c and Agent.h
        Data data; // i/o manager
        FILE *log; // FILE pointer for logs and debbug
        Features *feature;

    private:
        void SetRandomPosition(int n_size,int m_size); // Reset position randomly
        pair<int,int> getNextState(int action); // return the next state given an action
        int getReward(pair<int,int> state); // return the reward in the current state
        int getStateX(); // return the position x in the matrix of the map
        int getStateY(); // return the position y in the matrix of the map
        set<int> getValidActions(pair<int,int> state); // return the set of actions that is possible to make in the current state
        void setNextState(pair<int,int> nextState);
        void chooseFeature(int featureId);
        int getGhostsOneStepAway();
        int closestFood();
        int add_valid_neighbors(std::list<pair<pair<int,int>,int> > frontier,std::set<pair<pair<int,int>,int> > explored,std::pair<pair<int,int>,int> state);

    public:
        Environment(char **argv); // constructor
        void UpdateState(); // call the Update function of the class Agent so that he can decide the next move        

};