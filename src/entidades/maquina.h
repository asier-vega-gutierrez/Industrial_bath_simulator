
#include <vector>

#ifndef PROCESO_H
#define PROCESO_H

class Maquina {

    private:
        int id;
        std::vector<int> triggers; //los origenes de los eventos que desencadenan este proceso
        std::vector<bool> estados; //idica si el evento de la misma posicon que triggers ha ocurrido

    public:

        Maquina(int id, std::vector<int> triggers){
            this->id = id;
            for(int trigger : triggers){
                this->triggers.push_back(trigger);
                this->estados.push_back(false);
            }
        }

        int get_id(){return this->id;}

};


#endif
