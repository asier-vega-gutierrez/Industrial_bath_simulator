#include "../const.h"

#ifndef ENTRADA_H
#define ENTRADA_H

class Entrada {

    private:
        int id;
        int generador = LINEAR_CONGRUENTIAL_ENGINE;

    public:

        Entrada(int id, int generador){
            this->id = id;
            this->generador = generador;
        }

        int get_id(){return this->id;}

};


#endif
