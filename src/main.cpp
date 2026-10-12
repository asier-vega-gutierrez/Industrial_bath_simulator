#include "const.h"
#include "./evento/evento.h"
#include "./evento/cola.h"
#include "./generador/generador.h"
#include "./entidades/maquina.h"
#include "./config/config.h"

#include <iostream>
#include <random>
#include <vector>
#include <array>


void generar_eventos_entrada(ColaEventos& lista, int generador, int origen, double tiempo_simulacion, double frecuencia_llegada) {

    Generador gen = Generador(generador);

    double tiempo_actual = 0.0;

    while (tiempo_actual < tiempo_simulacion) {
        double tiempo_hasta_siguiente = gen.exponencial(frecuencia_llegada);
        tiempo_actual += tiempo_hasta_siguiente;

        if (tiempo_actual <= tiempo_simulacion) {
            // inserta el evento en la posición correcta según su tiempo
            lista.push(Evento(origen, EXTERNO, tiempo_actual));
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

std::vector<int> array_to_vector(const int* arr, size_t size) {
    return std::vector<int>(arr, arr + size);
}

int main() {


    // Configuración del yaml
    //https://github.com/jbeder/yaml-cpp
    //https://github.com/jbeder/yaml-cpp/blob/master/docs/Tutorial.md

    Config config = Config("../config/config.yaml");
    // std::vector<Maquina> lista_entradas = config.get_entradas();
    std::vector<Maquina> lista_maquinas = config.get_maquinas();
    // printf("%d \n", lista_maquinas[2].get_id());
    
    
    // Leer el modelo
    

    //general
    double tiempo_simulacion = 60.0; // 60 minutos
    //entrada ids = 0, 1
    int entrada = 2; //numero de entradas
    //frecuencia de cada entrada


    //procesos
    // const int num_procesos = 3;
    // int arr_1[1] = {0};
    // int arr_2[1] = {1};
    // int arr_3[2] = {2,3};
    // Proceso proceso_1 = Proceso(2, array_to_vector(arr_1, sizeof(arr_1)));
    // Proceso proceso_2 = Proceso(3, array_to_vector(arr_2, sizeof(arr_2)));
    // Proceso proceso_3 = Proceso(4, array_to_vector(arr_3, sizeof(arr_3)));
    // std::array<Proceso, num_procesos> lista_entidades = {proceso_1, proceso_2, proceso_3};

    

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




