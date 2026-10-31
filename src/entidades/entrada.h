#include "../const.h"
#include "../evento/evento.h"
#include "../generador/generador.h"

#ifndef ENTRADA_H
#define ENTRADA_H

class Entrada {

    private:
        int id;
        double tiempo_generacion = 0.0; // dunarante cuanto timepo se generan eventos
        unsigned int semilla = 0; // semilla para repertir la generacion
        int generador_tiempo = LINEAR_CONGRUENTIAL_ENGINE;
        int generador_lote = LINEAR_CONGRUENTIAL_ENGINE;
        int distribucion_tiempo = EXPONENCIAL;
        int distribucion_lote = ENTERO;

        // Segun que distribucion se necesita uno o dos parametros enteros o decimales
        std::variant<int, double> alpha_lote;
        std::variant<int, double> beta_lote;
        std::variant<int, double> alpha_tiempo;
        std::variant<int, double> beta_tiempo;

    public:

        Entrada(int id, double tiempo_generacion, int semilla, int generador_tiempo, int generador_lote, int distribucion_tiempo, int distribucion_lote, 
            std::variant<int, double> alpha_tiempo, std::variant<int, double> beta_tiempo, std::variant<int, double> alpha_lote, std::variant<int, double> beta_lote){

            this->id = id;
            this->tiempo_generacion = tiempo_generacion;
            this->semilla = semilla;
            this->generador_tiempo = generador_tiempo;
            this->generador_lote = generador_lote;
            this->distribucion_tiempo = distribucion_tiempo;
            this->distribucion_lote = distribucion_lote;
            
            this->alpha_tiempo = alpha_tiempo;
            this->beta_tiempo = beta_tiempo;
            this->alpha_lote = alpha_lote;
            this->beta_lote = beta_lote;
            
        }

        int get_id() const {return this->id;}
        double get_tiempo_generacion() const {return this->tiempo_generacion;}
        void generar_eventos(ColaEventos& lista, double tiempo_simulacion);

};


#endif
