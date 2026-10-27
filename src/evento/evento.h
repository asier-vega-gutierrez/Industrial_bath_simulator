

#include <vector>
#include <queue>
#include <iostream>

#ifndef EVENTO_H
#define EVENTO_H

// Eventos 
class Evento {
    private:
        // El origen del evento es el id de la entidad que lo provoca heredado
        int origen; // origen de evento (id de la entidad que lo genera)
        int tipo; // tipo de evento
        double tiempo; // instante en el que ocurre

    public:
        Evento() = default;
        Evento(int origen, int tipo, double tiempo){
            this->origen = origen;
            this->tipo = tipo;
            this->tiempo = tiempo;
        }
        int get_tipo() const {return this->tipo;}
        int get_origen() const {return this->origen;}
        double get_tiempo() const {return this->tiempo;}

};

// Estructura comparadora para ordenar los eventos por tiempo ascendente
struct CompararTiempo {
    bool operator()(const Evento& a, const Evento& b) const {
        return a.get_tiempo() > b.get_tiempo(); // '>' coloca el menor tiempo en la cima
    }
};

// Tipo definido para simplificar la firma de las funciones
using ColaEventos = std::priority_queue<Evento, std::vector<Evento>, CompararTiempo>;


//Cola de eventos para maquinas
class Cola {
    private:

        ColaEventos cola;
        int count_cola_actual = 0;
        int max_cola = 0;
        int min_cola = 0;

    public:

        Cola() = default;
        Cola(int tamano_cola){
            this->max_cola = tamano_cola;
        }

        bool add_event(Evento evento){
            if(count_cola_actual < max_cola){
                cola.push(evento);
                count_cola_actual += 1;
                return true;
            }else{
                return false;
            }
        }

        Evento get_event(){
            Evento evento_usar = cola.top();
            cola.pop();
            count_cola_actual -= 1;
            return evento_usar;
        }

        int get_max_cola() const {return this->max_cola;}
        int get_count_cola_actual() const {return this->count_cola_actual;}

};



#endif