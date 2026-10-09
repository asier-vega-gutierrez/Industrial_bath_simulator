
#ifndef PROCESO_H
#define PROCESO_H

class Proceso {

    private:
        int id;
        vector<int> triggers; //los origenes de entradas y/o los id de otros processo
        vector<bool> estados;

    public:

        Proceso(int id, int triggers[]){
            this->id = id;
            for(int trigger : triggers){
                this->triggers.push_back(trigger);
            }
        }

};


#endif
