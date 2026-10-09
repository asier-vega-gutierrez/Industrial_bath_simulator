
#ifndef EVENTO_H
#define EVENTO_H


class Evento {
    private:
        int tipo; // tipo de evento
        int origen; // origen de evento
        double tiempo; // instante en el que ocurre

    public:
        Evento() = default;
        Evento(int tipo, int origen, double tiempo){
            this->tipo = tipo;
            this->origen = origen;
            this->tiempo = tiempo;
        }
        int get_tipo(){return this->tipo;}
        int get_origen(){return this->origen;}
        double get_tiempo() const {return this->tiempo;}
        void generar_eventos_entrada();

};


#endif