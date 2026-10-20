#include "salida.h"

bool Salida::recoger_evento(Evento evento_actual){
    
    // Segun si el evento pertence a las relaciones de esta salida se actuliza se almacena el evento
    for(int i=0; i<(int)relaciones.size(); i++){
        if(relaciones[i] == evento_actual.get_origen()){
            this->eventos.push_back(evento_actual);
            return true;
        }
    }
    return false;
    
}