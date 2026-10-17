
#include "entidad.h"
#include "../evento/evento.h"
#include "../const.h"

#include <vector>
#include <algorithm>


#ifndef MAQUINA_H
#define MAQUINA_H

class Maquina: public Entidad {

    private:
        double tiempo = 0.0;
        double tiempo_bloqueo = 0.0;
        int prioridad = 1;
        std::vector<int> triggers = {}; //los origenes de los eventos que desencadenan esta maquina
        std::vector<bool> estados = {}; //idica si el evento de la misma posicion que triggers ha ocurrido

    public:

        Maquina(int id, std::vector<int> triggers, double tiempo, int prioridad) : Entidad(id){
            // this->id = id;
            this->tiempo = tiempo;
            this->prioridad = prioridad;
            for(int trigger : triggers){
                this->triggers.push_back(trigger);
                this->estados.push_back(false);
            }
        }

        int get_id(){return this->id;}
        // Este get se llama desde un puntero (const &) por lo que el metodo deve prometer (al compilador) que no va a modificar el objeto
        int get_prioridad() const {return this->prioridad;}
        // Llamar para actualizar el estado y generar los eventos
        bool actualizar_estado(int id_origen, ColaEventos& lista_eventos, double tiempo_actual);

};


#endif
