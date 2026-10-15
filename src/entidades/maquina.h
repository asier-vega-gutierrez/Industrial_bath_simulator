
#include <vector>
#include <algorithm>
#include "entidad.h"

#ifndef MAQUINA_H
#define MAQUINA_H

class Maquina: public Entidad {

    private:
        double tiempo;
        double tiempo_bloqueo = 0.0;
        std::vector<int> triggers = {}; //los origenes de los eventos que desencadenan esta maquina
        std::vector<bool> estados = {}; //idica si el evento de la misma posicion que triggers ha ocurrido

    public:

        Maquina(int id, std::vector<int> triggers, double tiempo) : Entidad(id){
            // this->id = id;
            this->tiempo = tiempo;
            for(int trigger : triggers){
                this->triggers.push_back(trigger);
                this->estados.push_back(false);
            }
        }

        int get_id(){return this->id;}

        bool actualizar_estado(int id_origen, ColaEventos& lista_eventos, double tiempo_actual){

            // Si la mauquina esta bloqueda no puede consumir eventos
            if (tiempo_actual < tiempo_bloqueo){
                return false;
            }

            bool evento_para_mi = false;

            // Segun si el evento pertence a los trigger de esta maquina se actuliza su correspondiente estado  
            for(int i=0; i<(int)triggers.size(); i++){
                if(triggers[i] == id_origen){
                    evento_para_mi = true;
                    if (estados[i] == false){
                        estados[i] = true;
                        printf("--- Maquina %d actualiza su estado\n", this->id);
                    }else{
                        return false;
                    }
                }
            }

            // Si el evento no era para esta máquina, salimos indicando que no lo consumió
            if (!evento_para_mi) {
                return false;
            }

            // Solo si todos los estados son True se genera un evento
            bool evento_listo = std::all_of(estados.begin(), estados.end(), [](bool v) { return v; });
            if(evento_listo){
                printf("--- Maquina %d a generado un evento\n", this->id);
                lista_eventos.push(Evento(this->id, INTERNO, tiempo_actual+this->tiempo));
                //si genera un evento la maquian se bloquea el tiempo que ejecute
                this->tiempo_bloqueo = tiempo_actual + this->tiempo;
                std::fill(this->estados.begin(), this->estados.end(), false);
            }

            // Devuelve true ya que el evento era suyo y lo consumio
            return true; 

        }

};


#endif
