#include "Features.h"
#include "Agent.h"

using namespace std;

class ApproximateAgent:public QLearningAgent{
    private:
        map<string,float> weights;
        Features *feature;
    public:
        ApproximateAgent();
        ApproximateAgent(int map_width,int map_height,Features *features);
        void Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate){
            this->feature->getFeatures(state,action);
            float difference = (float) learning_rate*(reward + discount*NextQValue - this->Qvalue[state.first][state.second][action]);

            std::set<string> f = this->feature->getFeaturesKeys();
            float result = 0;
//            printf("Difference: %f\n",difference);
            for(std::set<string>::const_iterator i = f.begin(); i != f.end(); i++){
                this->weights[(*i)] += difference*this->feature->features[(*i)];
//                 printf("%f %f\n",this->weights[(*i)],this->feature->features[(*i)]);
                result += this->weights[(*i)]*this->feature->features[(*i)];
                printf("weight[%s] = %f\nfeature[%s] = %f\nresult = %f\nstate:(%i,%i)\n",(*i).c_str(),this->weights[(*i)],(*i).c_str(),this->feature->features[(*i)],result,state.first,state.second);
            }
            printf("\n");
            this->Qvalue[state.first][state.second][action] = result;
            //printf("%f\n",this->Qvalue[state.first][state.second][action]);
        }
};