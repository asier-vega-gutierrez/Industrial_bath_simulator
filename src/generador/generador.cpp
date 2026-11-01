#include "generador.h"

// Distribuciones de tipo double para tiempos

// exponencial (Genera segun una frecuencia de aparicion de eventos)
double Generador::exponencial(double frecuencia){
    std::exponential_distribution<double> dist(frecuencia);
    // std::visit aplica la distribución al motor que esté activo
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Real uniforme (Genera eventos cada x minutos, donde x pertence al conjunto min max)
double Generador::real(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Normal (Genera eventos cada "media" minutos con una desviacion)
double Generador::normal(double media, double desviacion_estandar) {
    std::normal_distribution<double> dist(media, desviacion_estandar);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}


// Distribuciones de tipo int para lotes

// Entero uniforme (Genera una cantidad de elementos por lote entre min max)
int Generador::entero(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Binomial (Genera t pruebas donde la probabilidad de exito es p, los exitos son el tamaño del lote)
int Generador::binomial(int t, double p) {
    std::binomial_distribution<int> dist(t, p);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

// Poisson (Genera elementos de un lote segun una media, cuanto mas alejado de la madia este el valor mas dificil es que aparezca)
int Generador::poisson(double media) {
    std::poisson_distribution<int> dist(media);
    return std::visit([&](auto& arg) { return dist(arg); }, motor);
}

