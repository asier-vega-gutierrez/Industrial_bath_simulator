
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
    // Se almacen si el evento a sido procesado o se ha descartado
    if (evento_procesado) {
        this->eventos_procesados.push_back(evento);
    } else {
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
        copia.pop();
    }
}

void Resultado::procesar(){
    int count_eventos_iniciales = this->eventos_iniciales.size();
    int count_eventos_sinprocesar_ext = 0;
    for (Evento evento : this->eventos_sinprocesar){
        if(evento.get_tipo() == EXTERNO){
            count_eventos_sinprocesar_ext += 1;
        }
    }
    printf("%d\n", count_eventos_iniciales);
    printf("%d\n", count_eventos_sinprocesar_ext);
    double resultado = (double)count_eventos_sinprocesar_ext / (count_eventos_iniciales + count_eventos_sinprocesar_ext) * 100.0;
    printf("%f % \n", resultado);


}