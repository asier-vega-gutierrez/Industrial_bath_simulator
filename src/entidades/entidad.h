
#include "../registro/registro.h"

#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entidad {
    
    private:

    protected: // permite que las clases hija si accedan
        int id = 0;
        Registro registro = Registro();

    public:
        Entidad(int id){
            this->id = id;
        }
        int get_id(){return this->id;}
};


#endif


