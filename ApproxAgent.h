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

        float getQvalue(pair<int,int> state,int action){
            this->feature->getFeatures(state,action);
            float result = 0.0;
            std::set<string> f = this->feature->getFeaturesKeys();
            for(std::set<string>::const_iterator i = f.begin(); i != f.end(); i++){
                result += this->weights[(*i)]*this->feature->features[(*i)];
            }            
            this->Qvalue[state.first][state.second][action] = result;
            return this->Qvalue[state.first][state.second][action];
        }

        void Update(pair<int,int> state,pair<int,int> nextState,int action,float reward,float NextQValue,float discount,float learning_rate){
            float difference = (float) learning_rate*(reward + discount*NextQValue - this->getQvalue(state,action));
            printf("Q[%i][%i][%i] = %f\n",state.first,state.second,action,this->Qvalue[state.first][state.second][action]);
            fprintf(this->log,"learning_r: %f,reward: %f,discount: %f,NextQValue: %f,Q[state] : %f\n",learning_rate,reward,discount,NextQValue,this->Qvalue[state.first][state.second][action]);
            fprintf(this->log,"Q[%i][%i][%i] = %f\n",state.first,state.second,action,this->Qvalue[state.first][state.second][action]);
            std::set<string> f = this->feature->getFeaturesKeys();
            for(std::set<string>::const_iterator i = f.begin(); i != f.end(); i++){
                this->weights[(*i)] += difference*this->feature->features[(*i)];
            }
        }
};