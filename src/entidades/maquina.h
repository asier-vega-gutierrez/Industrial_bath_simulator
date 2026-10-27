
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
        std::vector<int> relaciones = {}; //los origenes de los eventos que desencadenan esta maquina
        std::vector<bool> estados = {}; //indica si el evento de la misma posicion que relaciones ha ocurrido
        std::vector<Cola> colas = {}; //para cada estado hay una cola
        // Esto vale para actulizar internamente los tiempos de la maquina
        double tiempo_ultimo = 0.0;
        double tiempo_produciendo = 0.0;
        double tiempo_sinproducir = 0.0;
        void actualizar_tiempos(double tiempo_actual);

    public:

        Maquina(int id, std::vector<int> relaciones, double tiempo, int prioridad, std::vector<int> tamano_cola) : Entidad(id){
            this->tiempo = tiempo;
            this->prioridad = prioridad;
            
            for (size_t i = 0; i < relaciones.size(); ++i) {
                this->relaciones.push_back(relaciones[i]);
                this->estados.push_back(false);
                Cola cola = Cola(tamano_cola[i]);
                this->colas.push_back(cola);
            }
        }

        int get_id() const {return this->id;}
        // Este get se llama desde un puntero (const &) por lo que el metodo deve prometer (al compilador) que no va a modificar el objeto
        int get_prioridad() const {return this->prioridad;}
        // Llamar para actualizar el estado y generar los eventos
        bool actualizar_estado(Evento evento, ColaEventos& lista_eventos, double tiempo_actual);
        double get_tiempo_produciendo() const {return this->tiempo_produciendo;}
        double get_tiempo_sinproducir() const {return this->tiempo_sinproducir;}
        std::vector<Cola> get_colas() const {return this->colas;}

};


#endif
