#include <set>
#include <list>
#include <map>

using namespace std;

class Features{
    private:
        char **map;

    public:
        std::map<string,float> features;

        Features();
        Features(char **map);
        int getGhostsOneStepAway(pair<int,int> state);
        int add_valid_neighbors(std::list<pair<pair<int,int>,int> > frontier,std::set<pair<pair<int,int>,int> > explored,std::pair<pair<int,int>,int> state);
        int closestFood(pair<int,int> initial_state);
        void getFeatures(pair<int,int> initial_state);
        std::set<string> getFeaturesKeys();
};