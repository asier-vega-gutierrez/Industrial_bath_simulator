#include "./const.h"
#include "./evento/evento.h"
#include "./generador/generador.h"
#include "./entidades/maquina.h"
#include "./config/config.h"
#include "./experimento/experimento.h"

#include <iostream>
#include <random>
#include <vector>
#include <array>


void simulacion(ColaEventos& lista_eventos, double tiempo_simulacion, std::vector<Maquina> lista_maquinas){

    double tiempo_actual = 0.0;

    // La simulacion termina si se excede el tiempo de simulacion
    while (tiempo_simulacion > tiempo_actual){

        printf("---------------------------------\n");
        printf("--- Nueva itieracion de simulacion \n");
        print_cola_eventos(lista_eventos);

        Evento evento_actual = lista_eventos.top();
        lista_eventos.pop();

        // Se actualiza el estado de las etidades tipo maquina
        bool evento_procesado = false;
        for (Maquina& maquina : lista_maquinas){
            // Si la máquina procesa el evento, devolvemos true y rompemos para que nadie más lo use
            if (maquina.actualizar_estado(evento_actual.get_origen(), lista_eventos, tiempo_actual)) {
                evento_procesado = true;
                break; // El evento ya fue consumido
            }
        }

        if (evento_procesado) {
            printf("--- Evento actual procesado \n");
        } else {
            printf("--- Evento actual NO procesado \n");
        }


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


    // Cargar la configuracion
    Config config = Config("../config/config.yaml");
    std::vector<Entrada> lista_entradas = config.get_entradas();
    std::vector<Maquina> lista_maquinas = config.get_maquinas();
    std::vector<Experimento> lista_experimentos = config.get_experimentos(); //TODO lo ultimo en implementar, cada experimiento tiene una cola de eventos???
    

    // Declaración de la cola de prioridad de eventos
    ColaEventos lista_eventos;
    // Generacion de todos los enventos externo
    for(Entrada entrada : lista_entradas){
        entrada.generar_eventos(lista_eventos, lista_experimentos[0].get_tiempo_simulacion());
    }


    simulacion(lista_eventos, lista_experimentos[0].get_tiempo_simulacion(), lista_maquinas);


    return 0;
}




