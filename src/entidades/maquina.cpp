
#include "maquina.h"

bool Maquina::actualizar_estado(int id_origen, ColaEventos& lista_eventos, double tiempo_actual){

    actualizar_tiempos(tiempo_actual);

    // Rutina de gestion de eventos

    // Si la mauquina esta bloqueda no puede consumir eventos
    if (tiempo_actual < tiempo_bloqueo){
        return false;
    }

    bool evento_para_mi = false;

    // Segun si el evento pertence a las relaciones de esta maquina se actuliza su correspondiente estado  
    for(int i=0; i<(int)relaciones.size(); i++){
        if(relaciones[i] == id_origen){
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

void Maquina::actualizar_tiempos(double tiempo_actual){
    // Acumular el tiempo transcurrido desde la ultima actualización
    if (tiempo_actual > tiempo_ultimo) {
        double delta = tiempo_actual - tiempo_ultimo;
        
        // Si al inicio del intervalo la maquina estaba bloqueada, parte o todo el tiempo fue de producción
        if (tiempo_ultimo < tiempo_bloqueo) {
            double fin_produccion = std::min(tiempo_actual, tiempo_bloqueo);
            double prod_delta = fin_produccion - tiempo_ultimo;
            tiempo_produciendo += prod_delta;
            
            // Si el tiempo actual superó el bloqueo, el resto del intervalo estuvo sin producir
            if (tiempo_actual > tiempo_bloqueo) {
                tiempo_sinproducir += (tiempo_actual - tiempo_bloqueo);
            }
        } else {
            // Si ya habia terminado su bloqueo, todo el intervalo transcurrido fue sin producir
            tiempo_sinproducir += delta;
        }
        
        tiempo_ultimo = tiempo_actual;
    }
}