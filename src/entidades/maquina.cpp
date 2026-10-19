
#include "maquina.h"

bool Maquina::actualizar_estado(int id_origen, ColaEventos& lista_eventos, double tiempo_actual){

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
                this->registro.print_entidad_estado(this->id);
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
        this->registro.print_entidad_generacion(this->id);
        lista_eventos.push(Evento(this->id, INTERNO, tiempo_actual+this->tiempo));
        //si genera un evento la maquian se bloquea el tiempo que ejecute
        this->tiempo_bloqueo = tiempo_actual + this->tiempo;
        std::fill(this->estados.begin(), this->estados.end(), false);
    }

    // Devuelve true ya que el evento era suyo y lo consumio
    return true; 

}