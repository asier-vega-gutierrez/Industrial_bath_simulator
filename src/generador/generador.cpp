#include "generador.h"


// exponencial (lambda = frecuencia)
double Generador::exponencial(double frecuencia){
    std::exponential_distribution<double> dist(frecuencia);
    // std::visit aplica la distribución al motor que esté activo
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Entero uniforme
int Generador::entero(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Real uniforme
double Generador::real(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}