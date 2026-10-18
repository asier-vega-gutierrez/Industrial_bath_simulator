#include "salida.h"

bool Salida::recoger_evento(Evento evento_actual){
    
    // Segun si el evento pertence a los trigger de esta salida se actuliza se alamacena el evento
    for(int i=0; i<(int)triggers.size(); i++){
        if(triggers[i] == evento_actual.get_origen()){
            this->eventos.push_back(evento_actual);
            return true;
        }
    }
    return false;
    
}