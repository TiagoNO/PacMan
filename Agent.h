#include <set>
#include <string>

using namespace std;

class QLearningAgent{
    private:
        float ***Qvalue;

    public:
        QLearningAgent();
        QLearningAgent(int map_width,int map_height); // constructor of the agent
        int getAction(set<int> validActions,pair<int,int> state); // get the best action to take in a certain state
        float getBestQValue(set<int> validActions,pair<int,int> state);
        float*** getQValues();
        void Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate);
                                                                                                            // Update the Q() function
};