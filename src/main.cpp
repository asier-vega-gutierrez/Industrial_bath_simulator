#include "./const.h"
#include "./evento/evento.h"
#include "./generador/generador.h"
#include "./entidades/maquina.h"
#include "./config/config.h"
#include "./experimento/experimento.h"
#include "./registro/registro.h"

#include <iostream>
#include <random>
#include <vector>
#include <array>

// Se ocupa de llamar a los subprogramas que realizan la simulacion
void monitor(ColaEventos& lista_eventos, double tiempo_simulacion, std::vector<Maquina> lista_maquinas, std::vector<Salida> lista_salidas){

    double tiempo_actual = 0.0;

    // Registro de actividad para monstrar toda la informacion durante la ejecucion
    Registro registro = Registro();
    registro.print_iniciar();

    // La simulacion termina si se excede el tiempo de simulacion
    while (tiempo_simulacion > tiempo_actual){

        registro.print_estado_sistema(lista_eventos.top());
        registro.print_cola_eventos(lista_eventos);

        // Se recoje el evento superiro de la lsita que es el primero en tiempo que va a ocurrir
        Evento evento_actual = lista_eventos.top();
        lista_eventos.pop(); // se elmina una vez recojido


        // RUTINA DE EVENTOS
        // aqui se procesa el evento hasta que es consumido
        bool evento_procesado = false;

        // Se actualiza el estado de las etidades tipo maquina
        for (Maquina& maquina : lista_maquinas){
            // Si la máquina procesa el evento, devolvemos true y salimos
            if (maquina.actualizar_estado(evento_actual.get_origen(), lista_eventos, tiempo_actual)) {
                evento_procesado = true;
                break; // El evento ya fue consumido
            }
        }

        // Si el evento no se a consumido en ninguna maquina el evento peude ser de salida del sistema
        if (!evento_procesado) {
            // Si el evento es final se deve guardar en su salida correspondiente
            for (Salida& salida : lista_salidas){
                // Si la salida consume el evento devolvemos true y salimos
                if (salida.recoger_evento(evento_actual)) {
                    evento_procesado = true;
                    break; // El evento ya fue consumido
                }
            }
        }

        // TODO esto se tiene que llamar desde resutlado
        registro.print_resultado_iteracion(evento_procesado);
        
        // RUTINA DE FINALIZACION
        // Rutina de finalizado de simulacion en caso de que se acaben los eventos
        if (lista_eventos.size() != 0){
            // Si no se han terminado los eventos se suma el tiempo hasta el siguiente evento
            Evento evento_siguiente = lista_eventos.top();
            tiempo_actual = evento_siguiente.get_tiempo();
        }else{
            // Se fuerza la finalizacion
            tiempo_actual = tiempo_simulacion;
        }
    }

    registro.print_finalizar();


    // TODO mover a clase resutlado o procesdo resultados se pinta desde la clase registro
    for (Salida salida : lista_salidas){
        printf("Eventos de la salida %d \n", salida.get_id());
        for(Evento ev : salida.get_eventos()){
            printf("> %d %d %f\n", ev.get_origen(), ev.get_tipo(), ev.get_tiempo());
        }
    }

}


// inicializa las  las entidades segun configuracion y la lista de eventos
void inicializacion(Config config){

    // Cargar la configuracion
    std::vector<Entrada> lista_entradas = config.get_entradas();
    std::vector<Maquina> lista_maquinas = config.get_maquinas();
    std::vector<Salida> lista_salidas = config.get_salidas();
    std::vector<Experimento> lista_experimentos = config.get_experimentos(); //TODO lo ultimo en implementar, cada experimiento tiene una cola de eventos???
    
    // Declaración de la cola de prioridad de eventos
    ColaEventos lista_eventos;
    // Generacion de todos los enventos externos
    for(Entrada entrada : lista_entradas){
        entrada.generar_eventos(lista_eventos, lista_experimentos[0].get_tiempo_simulacion());
    }

    // El ultimo paso de la inizacion es llamar al monitor para que comience la simulacion
    monitor(lista_eventos, lista_experimentos[0].get_tiempo_simulacion(), lista_maquinas, lista_salidas);

}

// Se le deve pasar en la primera posicion la ruta al archivo de configuracion
int main(int argc, char *argv[]) {
    Config config;
    if (argc > 1) {
        config = Config(argv[argc-1]);
        inicializacion(config);
    }else{
        printf("Introduce la ruta al fichero de configuracion\n");
    }
    
    return 0;
}

// Desde la carpeta build: make && ../bin/main ../config/config.yaml




