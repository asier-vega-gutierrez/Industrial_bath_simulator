
#include "resultado.h"

// Almacena la lista de eventos original
void Resultado::almacenar_inicial(ColaEventos lista_eventos){
    auto copia = lista_eventos;
    while (!copia.empty()) {
        this->eventos_iniciales.push_back(copia.top());
        copia.pop();
    }
}

// Almacena informacion al final de cada iteracion
void Resultado::almacenar_iteracion(bool evento_procesado, Evento evento){
    // Se almacena el evento en la lista completa
    this->eventos_lista_completa.push_back(evento);
    // Se almacen si el evento a sido procesado o se ha descartado
    if (evento_procesado) {
        this->eventos_procesados.push_back(evento);
    } else if (!evento_procesado){
        this->eventos_sinprocesar.push_back(evento);
    }
    // Se escribe un aviso para que esta accion quede registrada
    this->registro.print_resultado_iteracion(evento_procesado);
}

// Almacena la lista de eventos final
void Resultado::almacenar_final(ColaEventos lista_eventos){
    auto copia = lista_eventos;
    while (!copia.empty()) {
        this->eventos_finales.push_back(copia.top());
        //Tambien se guardan en la lista completa
        this->eventos_lista_completa.push_back(copia.top());
        copia.pop();
    }

}

void Resultado::procesar(){

    int count_eventos_ext = count_vector_tipo_evento(eventos_lista_completa, EXTERNO);
    int count_eventos_finales_ext = count_vector_tipo_evento(eventos_finales, EXTERNO);
    int count_eventos_sinprocesar_ext = count_vector_tipo_evento(eventos_sinprocesar, EXTERNO);

    // Porcentaje de los eventos EXTERNOs procesados y no 
    double eesp = (double)count_eventos_sinprocesar_ext / (count_eventos_ext - count_eventos_finales_ext);
    // printf("Cantidad de eventos EXTERNOs generados: %d\n", count_eventos_iniciales);
    printf("Cantidad de eventos EXTERNOs procesados: %d\n", count_eventos_ext - count_eventos_finales_ext - count_eventos_sinprocesar_ext);
    printf("Cantidad de eventos EXTERNOs sin procesar: %d\n", count_eventos_sinprocesar_ext);
    printf("Eventos EXTERNOs sin procesar: %f % \n", eesp * 100.0);
    printf("Eventos EXTERNOs procesados: %f % \n", (1-eesp) * 100.0);


    int count_eventos_int = count_vector_tipo_evento(eventos_lista_completa, INTERNO);
    int count_eventos_finales_int = count_vector_tipo_evento(eventos_finales, INTERNO);
    int count_eventos_sinprocesar_int = count_vector_tipo_evento(eventos_sinprocesar, INTERNO);

    // Porcentaje de los eventos INTERNOS procesados y no
    double eisp = (double)count_eventos_sinprocesar_int / (count_eventos_int - count_eventos_finales_int);
    // printf("Cantidad de eventos INTERNOs generados: %d\n", count_eventos_int);
    printf("Cantidad de eventos INTERNOs procesados: %d\n", count_eventos_int - count_eventos_finales_int - count_eventos_sinprocesar_int);
    printf("Cantidad de eventos INTERNOs sin procesar: %d\n", count_eventos_sinprocesar_int);
    printf("Eventos INTERNOs sin procesar: %f % \n", eisp * 100.0);
    printf("Eventos INTERNOs procesados: %f % \n", (1-eisp) * 100.0);

    for(const Salida& salida : this->lista_salidas){
        if (salida.get_count_eventos() != 0){
            printf("Cantidad de eventos de la salida %d es %d son: \n", salida.get_id(), salida.get_count_eventos());
            for(Evento ev : salida.get_eventos()){
                printf("> %d %d %f\n", ev.get_origen(), ev.get_tipo(), ev.get_tiempo());
            }
        }
    }

}

int Resultado::count_vector_tipo_evento(std::vector<Evento> lista,int tipo){
    int count = 0;
    for (Evento evento : lista){
        if(evento.get_tipo() == tipo){
            count += 1;
        }
    }
    return count;
}