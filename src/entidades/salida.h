#include "../evento/evento.h"


#ifndef SALIDA_H
#define SALIDA_H

class Salida {

    private:
        int id = 0;
        std::vector<int> triggers = {};
        std::vector<Evento> eventos = {};

    public:

        Salida(int id, std::vector<int> triggers){
            this->id = id;
            this->triggers = triggers;
        }

        int get_id(){return this->id;}
        std::vector<Evento> get_eventos(){return this-> eventos;}
        bool recoger_evento(Evento evento_actual);

};


#endif