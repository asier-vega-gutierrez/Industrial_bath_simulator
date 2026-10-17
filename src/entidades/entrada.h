#include "../const.h"
#include "../evento/evento.h"
#include "../generador/generador.h"

#ifndef ENTRADA_H
#define ENTRADA_H

class Entrada {

    private:
        int id;
        int generador = LINEAR_CONGRUENTIAL_ENGINE;
        double lambda;

    public:

        Entrada(int id, int generador, double lambda){
            this->id = id;
            this->generador = generador;
            this->lambda = lambda;
        }

        int get_id(){return this->id;}
        int get_generador(){return this->generador;}
        double get_lambda(){return this->lambda;}
        void generar_eventos(ColaEventos& lista, double tiempo_simulacion);

};


#endif
