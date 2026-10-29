#include "generador.h"


// Generadores de tiempo

// exponencial (lambda = frecuencia)
double Generador::exponencial(double frecuencia){
    std::exponential_distribution<double> dist(frecuencia);
    // std::visit aplica la distribución al motor que esté activo
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Real uniforme
double Generador::real(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Normal (Gaussian)
double Generador::normal(double media, double desviacion_estandar) {
    std::normal_distribution<double> dist(media, desviacion_estandar);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}



// Generadores de lotes

// Entero uniforme
int Generador::entero(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Binomial
int Generador::binomial(int t, double p) {
    std::binomial_distribution<int> dist(t, p);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Poisson (lambda / media)
int Generador::poisson(double media) {
    std::poisson_distribution<int> dist(media);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}