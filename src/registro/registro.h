
#include "../evento/evento.h"
#include <fstream>
#include "../const.h"

#ifndef REGISTRO_H
#define REGISTRO_H

// El resgitro "Registra" pinta informacion por consola
class Registro {

    private:
        
        void vaciar();
        const char* ruta = "";

    public:

        Registro(const char* ruta){
            this->ruta = ruta;
        }
        ~Registro() = default;


        void escribir(const std::string& mensaje);
        void print_iniciar_simulacion();
        void print_iniciar_informe();
        void print_cola_eventos(ColaEventos cola);

    };

#endif