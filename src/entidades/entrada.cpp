#include "entrada.h"

void Entrada::generar_eventos(ColaEventos& lista, double tiempo_simulacion) {

    Generador gen_tiempo = Generador(this->generador_tiempo, this->semilla);
    Generador gen_lote = Generador(this->generador_tiempo, this->semilla);

    double tiempo_actual = 0.0;

    while (tiempo_actual < tiempo_simulacion) {
        // double tiempo_hasta_siguiente = gen_tiempo.exponencial(std::get<double>(this->alpha));
        double tiempo_hasta_siguiente = gen_tiempo.exponencial(this->alpha);
        tiempo_actual += tiempo_hasta_siguiente;

        if (tiempo_actual <= tiempo_simulacion) {
            // int tamano_lote = gen_lote.entero(1, 1);
            // for (int i = 0; i < tamano_lote; ++i) {
                // inserta el evento en la posición correcta según su tiempo
                lista.push(Evento(this->id, EXTERNO, tiempo_actual));
            // }
        }
    }
}