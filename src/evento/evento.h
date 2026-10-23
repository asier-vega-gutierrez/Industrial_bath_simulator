

#include <vector>
#include <queue>
#include <iostream>

#ifndef EVENTO_H
#define EVENTO_H


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

#endif