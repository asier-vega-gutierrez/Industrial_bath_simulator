
#ifndef EVENTO_H
#define EVENTO_H


class Evento {
    private:
        // El origen del evento es el id de la entidad que lo provoca heredado
        int origen; // origen de evento (id de la entidad que lo genera)
        int tipo; // tipo de evento
        double tiempo; // instante en el que ocurre

    public:
        Evento() = default;
        Evento(int origen, int tipo, double tiempo){
            this->origen = origen;
            this->tipo = tipo;
            this->tiempo = tiempo;
        }
        int get_tipo(){return this->tipo;}
        int get_origen(){return this->origen;}
        double get_tiempo() const {return this->tiempo;}
        void generar_eventos_entrada();

};


#endif