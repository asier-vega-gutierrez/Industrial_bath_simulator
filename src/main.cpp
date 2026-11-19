#include "./const.h"
#include "./evento/evento.h"
#include "./generador/generador.h"
#include "./entidades/proceso.h"
#include "./config/config.h"
#include "./registro/registro.h"
#include "./resultado/resultado.h"

#include <iostream>
#include <random>
#include <vector>
#include <array>

// Se ocupa de llamar a los subprogramas que realizan la simulacion
void monitor(ColaEventos& lista_eventos, double tiempo_simulacion, std::vector<Entrada>& lista_entradas, std::vector<Proceso>& lista_procesos, std::vector<Salida>& lista_salidas){

    // El primer iontantes el el instantes del primer evento en la cola
    double tiempo_actual = lista_eventos.top().get_tiempo();

    // Esto alamcena la informacion durante la ejecucion para despues obtener la solucion de la simulacion
    Resultado resultado = Resultado(tiempo_simulacion, lista_entradas, lista_procesos, lista_salidas);
    resultado.almacenar_inicial(lista_eventos);

    // Registro de actividad para monstrar toda la informacion durante la ejecucion
    Registro registro = Registro(RUTA_REGISTRO);
    registro.print_iniciar_simulacion();
    
    // La simulacion termina si se excede el tiempo de simulacion
    while (tiempo_simulacion > tiempo_actual && !lista_eventos.empty()){
        
        std::string msg = "---------------------------------------------------------\n";
        msg += "--- Nueva iteracion de simulacion \n";
        msg += "--- El evento actual es: " + std::to_string(lista_eventos.top().get_origen()) + " " + std::to_string(lista_eventos.top().get_tipo()) + " " + std::to_string(lista_eventos.top().get_tiempo()) + " \n";
        registro.escribir(msg);
        registro.print_cola_eventos(lista_eventos);

        // Se recoje el evento superiro de la lsita que es el primero en tiempo que va a ocurrir
        Evento evento_actual = lista_eventos.top();
        lista_eventos.pop(); // se elmina una vez recojido

        // RUTINA DE EVENTOS
        // aqui se procesa el evento hasta que es consumido
        bool evento_procesado = false;

        // Se actualiza el estado de las etidades tipo proceso
        for (Proceso& proceso : lista_procesos){
            // Si la máquina procesa el evento, devolvemos true y salimos
            if (proceso.actualizar_estado(evento_actual, lista_eventos)) {
                evento_procesado = true;
                break; // El evento ya fue consumido
            }
        }

        // Si el evento no se a consumido en ninguna proceso el evento peude ser de salida del sistema
        if (!evento_procesado) {
            // Si el evento es final se deve guardar en su salida correspondiente
            for (Salida& salida : lista_salidas){
                // Si la salida consume el evento devolvemos true y salimos
                if (salida.recoger_evento(evento_actual)) {
                    std::string msg = "--- Evento de salida detectado \n";
                    registro.escribir(msg);
                    evento_procesado = true;
                    break; // El evento ya fue consumido
                }
            }
        }

        // Cada iteracion se almacena informacion para el resultado final
        resultado.almacenar_iteracion(evento_procesado, evento_actual);
        
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

    std::string msg = "--- La simulacion de este experimento a terminado\n";
    msg += "++++++++++++++++++++++++++++++++++++++++++++++++\n";
    registro.escribir(msg);


    // Al final se almacena informacion relevante
    resultado.almacenar_final(lista_eventos);

    resultado.procesar();

}


// inicializa las  las entidades segun configuracion y la lista de eventos
void inicializacion(Config config){

    // Cargar la configuracion
    std::vector<Entrada> lista_entradas = config.get_entradas();
    std::vector<Proceso> lista_procesos = config.get_procesos();
    std::vector<Salida> lista_salidas = config.get_salidas();
    
    // Declaración de la cola de prioridad de eventos
    ColaEventos lista_eventos;
    // Generacion de todos los enventos externos
    for(Entrada& entrada : lista_entradas){
        entrada.generar_eventos(lista_eventos, entrada.get_tiempo_generacion());
    }

    // El ultimo paso de la inizacion es llamar al monitor para que comience la simulacion
    monitor(lista_eventos, config.get_tiempo_simulacion(), lista_entradas, lista_procesos, lista_salidas);

    

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




