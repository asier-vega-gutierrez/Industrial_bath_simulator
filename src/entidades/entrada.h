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
        double tiempo_generacion = 0.0;

    public:

        Entrada(int id, int generador, double lambda, double tiempo_generacion){
            this->id = id;
            this->generador = generador;
            this->lambda = lambda;
            this->tiempo_generacion = tiempo_generacion;
        }

        int get_id() const {return this->id;}
        int get_generador() const {return this->generador;}
        double get_lambda() const {return this->lambda;}
        double get_tiempo_generacion() const {return this->tiempo_generacion;}
        void generar_eventos(ColaEventos& lista, double tiempo_simulacion);

};


#endif
