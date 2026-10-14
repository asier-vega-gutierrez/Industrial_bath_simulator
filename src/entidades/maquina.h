
#include <vector>
#include <algorithm>

#ifndef MAQUINA_H
#define MAQUINA_H

class Maquina {

    private:
        int id;
        double tiempo;
        std::vector<int> triggers; //los origenes de los eventos que desencadenan esta maquina
        std::vector<bool> estados; //idica si el evento de la misma posicion que triggers ha ocurrido
        // std::vector<bool> estados_count;

    public:

        Maquina(int id, std::vector<int> triggers, double tiempo){
            this->id = id;
            this->tiempo = tiempo;
            for(int trigger : triggers){
                this->triggers.push_back(trigger);
                this->estados.push_back(false);
            }
        }

        int get_id(){return this->id;}

        void actualizar_estado(int id_origen, ColaEventos& lista_eventos, double tiempo_actual){  
            // Segun si el evento pertence a los trigger de esta maquina se actuliza su correspondiente estado  
            for(int i=0; i<(int)triggers.size(); i++){
                if (triggers[i] == id_origen){
                    estados[i] = true;
                }
            }
            // Solo si todos los estados son True se genera un evento
            bool evento_listo = std::all_of(estados.begin(), estados.end(), [](bool v) { return v; });
            if(evento_listo){
                printf("--- Maquina %d a generado un evento \n", this->id);
                lista_eventos.push(Evento(this->id, INTERNO, tiempo_actual+this->tiempo));
                for (auto estado : this->estados){
                    estado = false;
                }
            }

            // printf("%d \n", (int)evento_listo);
        }

};


#endif
