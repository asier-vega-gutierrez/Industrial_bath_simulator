#include "../const.h"

#include <random>
#include <variant>

#ifndef GENERADOR_H
#define GENERADOR_H

class Generador {

    private:

        // esto es un generador de numeros alatorios que se base en entropía del hardware (ruido y fluctiuaciones del sistema)
        // se emplea com semilla para los tres generadores psudoaleatorios
        std::random_device rd;
        // esto almacena los tres motores posibles que se van a utilizar
        std::variant<std::minstd_rand, std::mt19937, std::ranlux48> motor;


    public:

        // Constructor: 1 = LCG, 2 = Ranlux, 3 = Mersenne Twister
        Generador(int tipo) { //https://stackoverflow.com/questions/77410508/is-it-safe-to-use-stdmt19937-with-fixed-seed-within-unit-tests
            if (tipo == LINEAR_CONGRUENTIAL_ENGINE) {
                motor = std::minstd_rand(rd());
            } else if (tipo == SUBTRACT_WITH_CARRY_ENGINE) {
                motor = std::ranlux48(rd());
            } else if (tipo == MERSENNE_TWISTER_ENGINE) {
                motor = std::mt19937(rd());
            }
        }

        // exponencial (lambda = frecuencia)
        double exponencial(double frecuencia);
        // Entero uniforme
        int entero(int min, int max);
        // Real uniforme
        double real(double min, double max);

    };

#endif
