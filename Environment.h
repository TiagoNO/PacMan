#include <string>
#include <stdlib.h>
#include <time.h>
#include "DataReader.h"
#include <set>

using namespace std;

class Environment{
    private:
        int state_x; // position x in the matrix
        int state_y; // position y in the matrix
        int n_size;  // max size in x of the map
        int m_size;  // max size in y of the map
        char **map;  // matrix of chars that represent the map

    public:
        Environment(int n_size,int m_size,char **map); // constructor
        void ResetPosition(int n_size,int m_size); // Reset position randomly
        void UpdateState(); // call the Update function of the class Agent so that he can decide the next move

        int getReward(); // return the reward in the current state
        int getStateX(); // return the position x in the matrix of the map
        int getStateY(); // return the position y in the matrix of the map
        set<string> getValidActions(); //return the set of actions that is possible to make in the current state
};



int main(){

}