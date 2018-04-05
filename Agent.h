#include <set>
#include <string>

using namespace std;

class QLearningAgent{
    private:
        float ***Qvalue; // matrix of Q-Values that map a 3-tuple(x,y,action) to a value
        FILE *log; // FILE pointer for logs and debbug
    public:
        QLearningAgent();
        QLearningAgent(int map_width,int map_height); // constructor of the agent
        int getAction(set<int> validActions,pair<int,int> state); // get the best action to take in a certain state
        float getBestQValue(set<int> validActions,pair<int,int> state); // return the best Q value in a given state
        float*** getQValues(); // return the matrix of values
        void Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate);
                                                                                                            // Update the Q() function
};