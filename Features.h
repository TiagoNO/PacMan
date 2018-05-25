#include <set>
#include <list>
#include <string>
#include <map>

#define acima 0
#define abaixo 1
#define esquerda 2
#define direita 3

using namespace std;

class Features{
    private:
        char **map;
        int map_h;
        int map_w;

    public:
        std::map<string,float> features;

        Features();
        Features(char **map,int map_width,int map_height);
        int getGhostsOneStepAway(pair<int,int> state);
        int add_valid_neighbors(std::list<pair<pair<int,int>,int> > *frontier,std::set<pair<int,int> > explored,std::pair<pair<int,int>,int> state);
        float closestFood(pair<int,int> initial_state);
        void getFeatures(pair<int,int> initial_state,int action);
        pair<int,int> calculateNextState(pair<int,int> initial_state,int action);
        std::set<string> getFeaturesKeys();
        bool isValid(pair<int,int> initial_state);
        bool is_goal(pair<int,int> state);
        float enemyNearby(pair<int,int> nextState);
};