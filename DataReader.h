using namespace std;

class Data{

    private: 
        char* dir; // directory of the info we need
        char** map; // the map where the agent will act
        float learning_rate; // learning rate
        float discount; // discount rate
        int n_size; // width of the map
        int m_size; // height of the map
        int num_iterations; // the number os plays that the agent can do
        FILE *log; // FILE pointer for logs and debbug

    private:
        void setMap();
    
    public:
        Data();
        Data(char **argv);
        char* getDir();
        char** getMap();
        float getDiscount();
        float getLearning_rate();
        int getWidth();
        int getHeight();
        int getNumIterations();
        void WriteQValues(float ***QValue);
        void WritePolicy(float ***QValue);
};