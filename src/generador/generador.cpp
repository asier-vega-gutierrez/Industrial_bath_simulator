#include "generador.h"


// exponencial (Genera segun una frecuencia de aparicion de eventos)
double Generador::exponencial(double frecuencia){
    std::exponential_distribution<double> dist(frecuencia);
    // std::visit aplica la distribución al motor que esté activo
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Entero uniforme (Genera eventos cada x minutos, donde x pertence al conjunto min max)
int Generador::entero(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Normal (Genera eventos cada "media" minutos con una desviacion)
double Generador::normal(double media, double desviacion_estandar) {
    std::normal_distribution<double> dist(media, desviacion_estandar);
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