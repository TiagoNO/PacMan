#include <set>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <float.h>

using namespace std;

class QLearningAgent{
    protected:
        float ***Qvalue; // matrix of Q-Values that map a 3-tuple(x,y,action) to a value
        FILE *log; // FILE pointer for logs and debbug
    public:
        QLearningAgent();
        QLearningAgent(int map_width,int map_height); // constructor of the agent
        int getAction(set<int> validActions,pair<int,int> state); // get the best action to take in a certain state
        float getBestQValue(set<int> validActions,pair<int,int> state); // return the best Q value in a given state
        float*** getQValues(); // return the matrix of values
        virtual float getQvalue(pair<int,int> state,int action);
        virtual void Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate);
                                                                                                            // Update the Q() function
};