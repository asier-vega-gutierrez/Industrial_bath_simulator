#include "const.h"
#include "./eventos/evento.h"
#include "./eventos/cola.h"
#include "./generador/generador.h"
#include <iostream>
#include <random>


void generar_eventos_entrada(ColaEventos& lista, int generador, int origen, double tiempo_simulacion, double frecuencia_llegada) {

    Generador gen = Generador(generador);

    double tiempo_actual = 0.0;

    while (tiempo_actual < tiempo_simulacion) {
        double tiempo_hasta_siguiente = gen.exponencial(frecuencia_llegada);
        tiempo_actual += tiempo_hasta_siguiente;

        if (tiempo_actual <= tiempo_simulacion) {
            // inserta el evento en la posición correcta según su tiempo
            lista.push(Evento(EXTERNO, origen, tiempo_actual));
        }
    }
}


void simulacion(ColaEventos& lista_eventos, double tiempo_simulacion){

    double tiempo_actual = 0.0;

    // La simulacion peude terminar si se excede el tiempo de simulacion
    while (tiempo_simulacion > tiempo_actual){
        Evento evento_actual = lista_eventos.top();
        lista_eventos.pop();
        //un evento desencadena una proceso con dependencia en ese evento


        printf("--- evento procesado \n");

        // Rutina de finalizado de simulacion en caso de que se acaben los eventos
        if (lista_eventos.size() != 0){
            Evento evento_siguiente = lista_eventos.top();
            tiempo_actual = evento_siguiente.get_tiempo(); // sele suma el tiempo del proceso
        }else{
            tiempo_actual = tiempo_simulacion;
        }

    }

}


int main() {


    // Configuración del yaml
    //general
    double tiempo_simulacion = 60.0; // 60 minutos
    //entrada
    int entrada = 2; //numero de entradas
    //frecuencia de cada entrada
    //procesos
    int proceso = 3;
    

    // Declaración de la cola de prioridad de eventos
    ColaEventos lista_eventos;
    generar_eventos_entrada(lista_eventos, LINEAR_CONGRUENTIAL_ENGINE, 1, tiempo_simulacion, 0.2);
    generar_eventos_entrada(lista_eventos, LINEAR_CONGRUENTIAL_ENGINE, 2, tiempo_simulacion, 0.1);



    simulacion(lista_eventos, tiempo_simulacion);



    while (!lista_eventos.empty()) {
        Evento actual = lista_eventos.top();
        lista_eventos.pop();                 

        printf("%d %d %.2f \n", actual.get_tipo(), actual.get_origen(), actual.get_tiempo());
    }




    return 0;
}




