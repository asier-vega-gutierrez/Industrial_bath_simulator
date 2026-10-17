

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
        int get_tipo(){return this->tipo;}
        int get_origen(){return this->origen;}
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

// TODO esto deve ir en una clase log que haga las de registro de actividad, entoces eleminar el inline
void inline print_cola_eventos(ColaEventos& cola){
    ColaEventos copia = cola;
    while (!copia.empty()) {
        Evento ev = copia.top();
        printf("%d %d %f\n", ev.get_origen(), ev.get_tipo(), ev.get_tiempo());
        copia.pop(); // Remove the top element to access the next one
    }
}

#endif