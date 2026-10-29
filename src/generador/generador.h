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

        // Función auxiliar para inicializar el motor según el tipo y la semilla
        // Constructor: 1 = LCG, 2 = Ranlux, 3 = Mersenne Twister
        //https://stackoverflow.com/questions/77410508/is-it-safe-to-use-stdmt19937-with-fixed-seed-within-unit-tests
        template <typename T>
        void inicializar_motor(int tipo, T semilla) {
            if (tipo == LINEAR_CONGRUENTIAL_ENGINE) {
                motor = std::minstd_rand(semilla);
            } else if (tipo == SUBTRACT_WITH_CARRY_ENGINE) {
                motor = std::ranlux48(semilla);
            } else if (tipo == MERSENNE_TWISTER_ENGINE) {
                motor = std::mt19937(semilla);
            } else {
                // Si llega un tipo no soportado, se usa una opción segura por defecto para evitar
                // un estado no inicializado del std::variant y un acceso inválido posterior.
                motor = std::minstd_rand(semilla);
            }
        }

    public:


        // Constructor: por hardware (entropía) o con semilla fija (para tests)
        Generador(int tipo, unsigned int semilla){
            if(semilla == 0){
                inicializar_motor(tipo, this->rd());
            }else{
                inicializar_motor(tipo, semilla);
            }
        }


        // exponencial (lambda = frecuencia)
        double exponencial(double frecuencia);
        // Entero uniforme
        int entero(int min, int max);
        // Real uniforme
        double real(double min, double max);
        // Normal / Gaussiana (media, desviación estándar)
        double normal(double media, double desviacion_estandar);
        // Binomial (t = número de ensayos, p = probabilidad de éxito)
        int binomial(int t, double p);
        // Poisson (lambda = media esperada)
        int poisson(double media);

    };

#endif
