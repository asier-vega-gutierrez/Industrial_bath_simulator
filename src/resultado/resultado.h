
#include "../evento/evento.h"
#include "../registro/registro.h"
#include "../entidades/salida.h"
#include "../entidades/maquina.h"
#include "../const.h"

#include <vector>
#include <memory>

#ifndef RESULTADO_H
#define RESULTADO_H


// Los resultado se recojen desde esta clase (inicio, iteracion y final) y cada entidad tambien recolecta informacion sobre si misma
class Resultado {

    private:

        double tiempo_simulacion = 0.0;
        const std::vector<Salida>& lista_salidas;
        const std::vector<Maquina>& lista_maquinas;

        std::vector<Evento> eventos_lista_completa = {}; //lista completa de todos los eventos que han aparecido
        std::vector<Evento> eventos_iniciales = {}; //eventos generados de forma inicila (todo EXTERNOs)
        std::vector<Evento> eventos_finales = {}; //eventos finales que no se han procesado
        std::vector<Evento> eventos_procesados = {}; //eventos que si se han procesado
        std::vector<Evento> eventos_sinprocesar = {}; //eventos que no se han podio procesar
        Registro registro = Registro();

        int count_vector_tipo_evento(std::vector<Evento> lista,int tipo);

    public:

        //Las entidades llegan solo como referencia de solo lectura
        Resultado(double tiempo_simulacion, const std::vector<Salida>& lista_salidas, const std::vector<Maquina>& lista_maquinas) 
            : lista_salidas(lista_salidas), lista_maquinas(lista_maquinas){
            this->tiempo_simulacion = tiempo_simulacion;
        }

        void almacenar_inicial(ColaEventos lista_eventos);
        void almacenar_iteracion(bool evento_procesado, Evento evento);
        void almacenar_final(ColaEventos lista_eventos);
        void procesar();

        //TODO saber por que el evento no se ha podido procesar
        //TODO saber si la simulacion a terminado con todos los eventos en el tiempo establecido
        //TODO saber que eventos ha dejado sin procesar por tiempo

};

#endif