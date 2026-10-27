
#include "../evento/evento.h"

#ifndef REGISTRO_H
#define REGISTRO_H

// El resgitro "Registra" pinta informacion por consola
class Registro {

    private:
        const char* cabecera_informacion = "--- "; //si se llama desde el registro del monitor
        const char* cabecera_accion = "--> "; //si se llama desde el registro de una entidad
        const char* cabecera_resultado = "--{ "; //si se llama desde el registro de los resultados

    public:

        Registro() = default;

        void print_iniciar();
        void print_finalizar();
        void print_cola_eventos(ColaEventos cola);
        void print_estado_sistema(Evento ev);
        void print_resultado_iteracion(bool flag);
        void print_entidad_estado(int id);
        void print_entidad_generacion(int id);
        void print_cola_llena(int id);
        void print_anadir_cola(int id, int actual);
        void print_anadir_denuevo_cola(int id, int actual);
        void print_elminar_cola(int id, int actual);

    };

#endif