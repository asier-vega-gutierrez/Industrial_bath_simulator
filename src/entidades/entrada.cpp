#include "entrada.h"

void Entrada::generar_eventos(ColaEventos& lista, double tiempo_simulacion) {

    Generador gen = Generador(this->generador);

    double tiempo_actual = 0.0;

    while (tiempo_actual < tiempo_simulacion) {
        double tiempo_hasta_siguiente = gen.exponencial(this->lambda);
        tiempo_actual += tiempo_hasta_siguiente;

        if (tiempo_actual <= tiempo_simulacion) {
            // inserta el evento en la posición correcta según su tiempo
            lista.push(Evento(this->id, EXTERNO, tiempo_actual));
        }
    }
}