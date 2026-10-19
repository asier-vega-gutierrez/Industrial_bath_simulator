#include "registro.h"


void Registro::print_estado_sistema(Evento ev){
    printf("---------------------------------------------------------\n");
    printf("%sNueva itieracion de simulacion \n", this->cabecera_informacion);
    printf("%sEl evento actual es: %d %d %f \n", this->cabecera_informacion, ev.get_origen(), ev.get_tipo(), ev.get_tiempo());
}

void Registro::print_cola_eventos(ColaEventos cola){
    ColaEventos copia = cola;
    printf("%sLista de eventos: \n", this->cabecera_informacion);
    while (!copia.empty()) {
        Evento ev = copia.top();
        printf("> %d %d %f\n", ev.get_origen(), ev.get_tipo(), ev.get_tiempo());
        copia.pop(); // Remove the top element to access the next one
    }
}

void Registro::print_iniciar(){
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("%sLa simulacion de este experimento a comenzado\n", this->cabecera_informacion);
}

void Registro::print_finalizar(){
    printf("%sLa simulacion de este experimento a terminado\n", this->cabecera_informacion);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void Registro::print_entidad_estado(int id){
    printf("%sMaquina %d actualiza su estado\n", this->cabecera_accion, id);
}   

void Registro::print_entidad_generacion(int id){
    printf("%sMaquina %d a generado un evento\n", this->cabecera_accion, id);
}   



// TODO esto se tien que llamar desde resutlado
void Registro::print_resultado_iteracion(bool flag){
    if (flag) {
        printf("%sEvento actual procesado \n", this->cabecera_informacion);
    } else {
        printf("%sEvento actual NO procesado \n", this->cabecera_informacion);
    }
}