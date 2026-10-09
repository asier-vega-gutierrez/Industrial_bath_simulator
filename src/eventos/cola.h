#include "evento.h"
#include <vector>
#include <queue>

#ifndef COLA_H
#define COLA_H

// Estructura comparadora para ordenar los eventos por tiempo ascendente
struct CompararTiempo {
    bool operator()(const Evento& a, const Evento& b) const {
        return a.get_tiempo() > b.get_tiempo(); // '>' coloca el menor tiempo en la cima
    }
};

// Tipo definido para simplificar la firma de las funciones
using ColaEventos = std::priority_queue<Evento, std::vector<Evento>, CompararTiempo>;


#endif