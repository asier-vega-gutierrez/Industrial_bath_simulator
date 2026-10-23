#include "../evento/evento.h"


#ifndef SALIDA_H
#define SALIDA_H

class Salida {

    private:
        int id = 0;
        std::vector<int> relaciones = {};
        std::vector<Evento> eventos = {};
        int count_eventos = 0;

    public:

        Salida(int id, std::vector<int> relaciones){
            this->id = id;
            this->relaciones = relaciones;
        }

        int get_id() const {return this->id;}
        std::vector<Evento> get_eventos() const {return this-> eventos;}
        int get_count_eventos() const {return this->count_eventos;}
        bool recoger_evento(Evento evento_actual);
        

};


#endif