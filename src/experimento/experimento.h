#include <string>

#ifndef EXPERIMENTO_H
#define EXPERIMENTO_H

class Experimento {

    private:
        std::string nombre = "None";
        double tiempo_simulacion = 0.0;

    public:

        Experimento(std::string nombre, double tiempo_simulacion){
            this->nombre = nombre;
            this->tiempo_simulacion = tiempo_simulacion;
        }

        std::string get_nombre(){return this->nombre;}
        int get_tiempo_simulacion(){return this->tiempo_simulacion;}

};



#endif