
#include "maquina.h"

bool Maquina::actualizar_estado(Evento evento, ColaEventos& lista_eventos, double tiempo_actual){

    actualizar_tiempos(tiempo_actual);

    // Rutina de gestion de eventos

    // 1. Buscar el índice correspondiente al origen del evento
    int indice = -1;
    for (int i = 0; i < (int)relaciones.size(); i++) {
        if (relaciones[i] == evento.get_origen()) {
            indice = i;
            break; // Encontramos la relación, salimos del bucle
        }
    }

    // Si el evento no pertenece a ninguna relación conocida de esta máquina no hay nada mas que hacer
    if (indice == -1) {
        return false; 
    }

    // 2. Intentar almacenar el evento entrante en su respectiva cola
    // solo en el caso que no se un evento de interrupcion (los eventos de interupcion siempre estan almacenados en una cola)
    if (evento.get_tipo() != INTERRUPCION){
        if (!this->colas[indice].add_event(evento)) {
            // Cola llena, el evento no se puede procesar ni almacenar
            // printf("--- Cola de maquina %d llena \n", this->id);
            this->registro.print_cola_llena(this->id);
            return false;
        } else {
            this->registro.print_anadir_cola(this->id, this->colas[indice].get_count_cola_actual());
        }
    }

    // 3. Si la máquina está bloqueada, aquí termina su trabajo (no puede consumir)
    if (tiempo_actual < tiempo_bloqueo) {
        // Si se almacena una evento en cola y la maquina esta bloquedad, este evento no se va ha procesar en el tiempo en el que llega por lo que:
        // se anade un evento tipo interrupcion por cada evento que se anada a la cola en esta situacion
        // este tiene el mismo origen que el evento introducido en la cola
        // esto permite que el sistema actualice en el momento que se desbloque
        lista_eventos.push(Evento(evento.get_origen(), INTERRUPCION, tiempo_actual+this->tiempo));
        if (evento.get_tipo() == INTERRUPCION){
            this->registro.print_anadir_denuevo_cola(this->id, this->colas[indice].get_count_cola_actual());
        }
        return true;
    }

    // 4. Si la máquina NO está bloqueada, procedemos a consumir de las colas solo si el estado está libre
    colas[indice].get_event();
    this->registro.print_elminar_cola(this->id, this->colas[indice].get_count_cola_actual());
    estados[indice] = true;
    this->registro.print_entidad_estado(this->id);

    // 5. Solo si todos los estados son True se genera un evento
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