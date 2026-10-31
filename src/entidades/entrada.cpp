#include "entrada.h"

void Entrada::generar_eventos(ColaEventos& lista, double tiempo_simulacion) {

    Generador gen_tiempo = Generador(this->generador_tiempo, this->semilla);
    Generador gen_lote = Generador(this->generador_lote, this->semilla);

    double tiempo_actual = 0.0;

    // Funcion para extarer del variant como double
    auto as_double = [](const auto& v) { 
        return std::visit([](auto arg) -> double { return arg; }, v); 
    };
    
    // Funcion para extarer del variant como int
    auto as_int = [](const auto& v) { 
        return std::visit([](auto arg) -> int { return arg; }, v); 
    };

    while (tiempo_actual < tiempo_simulacion) {

        double tiempo_hasta_siguiente = 0.0;
        // Segun la ditribucion de tiempo escojido en la cofiguracion
        switch (this->distribucion_tiempo) {
            case EXPONENCIAL: 
                tiempo_hasta_siguiente = gen_tiempo.exponencial(as_double(this->alpha_tiempo));
            break;
            case REAL:
                tiempo_hasta_siguiente = gen_tiempo.real(as_double(this->alpha_tiempo), as_double(this->beta_tiempo));
            break;
            case NORMAL:
                tiempo_hasta_siguiente = gen_tiempo.normal(as_double(this->alpha_tiempo), as_double(this->beta_tiempo));
            break;
        }
        
        tiempo_actual += tiempo_hasta_siguiente;

        if (tiempo_actual <= tiempo_simulacion) {
            // int tamano_lote = gen_lote.entero(1, 1);
            int tamano_lote = 1;
            switch (this->distribucion_lote) {
                case ENTERO: 
                    tamano_lote = gen_lote.entero(as_int(this->alpha_lote),as_int(this->beta_lote));
                break;
                case BINOMIAL:
                    tamano_lote = gen_lote.binomial(as_int(this->alpha_lote), as_double(this->beta_lote));
                break;
                case POISSON:
                    tamano_lote = gen_lote.poisson(as_int(this->alpha_lote));
                break;
            }
            // for (int i = 0; i < tamano_lote; ++i) {
                // inserta el evento en la posición correcta según su tiempo
                lista.push(Evento(this->id, EXTERNO, tiempo_actual));
            // }
        }
    }



}

