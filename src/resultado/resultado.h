
#include "../evento/evento.h"
#include "../registro/registro.h"
#include "../const.h"

#include <vector>

#ifndef RESULTADO_H
#define RESULTADO_H


class Resultado {

    private:
        std::vector<Evento> eventos_lista_completa = {}; //lista completa de todos los eventos que han aparecido
        std::vector<Evento> eventos_iniciales = {}; //eventos generados de forma inicila (todo EXTERNOs)
        std::vector<Evento> eventos_finales = {}; //eventos finales que no se han procesado
        std::vector<Evento> eventos_procesados = {}; //eventos que si se han procesado
        std::vector<Evento> eventos_sinprocesar = {}; //eventos que no se han podio procesar
        Registro registro = Registro();

    public:
        void almacenar_inicial(ColaEventos lista_eventos);
        void almacenar_iteracion(bool evento_procesado, Evento evento);
        void almacenar_final(ColaEventos lista_eventos);
        void procesar();

        //TODO de los eventos EXTERNO porcentaje y numero de los que se han procesado y no (comparar eventos_iniciales frente a eventos_sin_procesar)
        //TODO de los eventos INTERNOS porcentaje y numero de los que se han procesado y no

        //TODO saber por que el evento no se ha podido procesar
        //TODO saber si la simulacion a terminado con todos los eventos en el tiempo establecido
        //TODO saber que eventos ha dejado sin procesar por tiempo
    

};

#endif