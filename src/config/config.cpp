
#include "config.h"

double Config::get_tiempo_simulacion() {
    return config["simulacion"]["tiempo_simulacion"].as<double>();
}

unsigned int Config::get_semilla() {
    return config["simulacion"]["semilla"].as<int>();
}


std::vector<Entrada> Config::get_entradas() {
    std::vector<Entrada> lista;
    const auto& elementos = config["modelo"]["entidades"];
    for (const auto& elm : elementos) {
        if (elm["tipo"].as<std::string>() == "entrada"){
            int generador_tiempo = get_generador(elm["generador_tiempo"].as<std::string>());
            int generador_lote = get_generador(elm["generador_lote"].as<std::string>());
            int distribucion_tiempo = get_ditribucion_timepo(elm["ditribucion_tiempo"]["tipo"].as<std::string>());
            int distribucion_lote = get_ditribucion_lote(elm["ditribucion_lote"]["tipo"].as<std::string>());
            // Lectura segura de alpha y beta para el tiempo (con valor por defecto 0.0 si no existen)
            double alpha_tiempo = elm["ditribucion_tiempo"]["alpha"] ? elm["ditribucion_tiempo"]["alpha"].as<double>() : 0.0;
            double beta_tiempo = elm["ditribucion_tiempo"]["beta"] ? elm["ditribucion_tiempo"]["beta"].as<double>() : 0.0;
            // Lectura segura de alpha y beta para el lote (con valor por defecto 0.0 si no existen)
            double alpha_lote = elm["ditribucion_lote"]["alpha"] ? elm["ditribucion_lote"]["alpha"].as<double>() : 0.0;
            double beta_lote = elm["ditribucion_lote"]["beta"] ? elm["ditribucion_lote"]["beta"].as<double>() : 0.0;
            Entrada entrada = Entrada(elm["id"].as<int>(), elm["tiempo_generacion"].as<double>(), this->get_semilla(), generador_tiempo, generador_lote, distribucion_tiempo, distribucion_lote, alpha_tiempo, beta_tiempo, alpha_lote, beta_lote);
            lista.push_back(entrada);
        }
    }
    return lista;
}

int Config::get_generador(std::string str){
    if(!str.compare("LINEAR_CONGRUENTIAL_ENGINE")) {
        return LINEAR_CONGRUENTIAL_ENGINE;
    } else if(!str.compare("SUBTRACT_WITH_CARRY_ENGINE")){
        return SUBTRACT_WITH_CARRY_ENGINE;
    } else if(!str.compare("MERSENNE_TWISTER_ENGINE")){
        return MERSENNE_TWISTER_ENGINE;
    }

    return LINEAR_CONGRUENTIAL_ENGINE;
}

int Config::get_ditribucion_timepo(std::string str){
    if(!str.compare("EXPONENCIAL")) {
        return EXPONENCIAL;
    } else if(!str.compare("ENTERO")){
        return ENTERO;
    } else if(!str.compare("NORMAL")){
        return NORMAL;
    }

    return EXPONENCIAL;
}

int Config::get_ditribucion_lote(std::string str){
    if(!str.compare("ENTERO")) {
        return ENTERO;
    } else if(!str.compare("BINOMIAL")){
        return BINOMIAL;
    } else if(!str.compare("POISSON")){
        return POISSON;
    }

    return ENTERO;
}


std::vector<Maquina> Config::get_maquinas() {
    std::vector<Maquina> lista;
    const auto& elemento = config["modelo"]["entidades"];
    for (const auto& elm : elemento) {
        if (elm["tipo"].as<std::string>() == "maquina"){
            Maquina maq = Maquina(elm["id"].as<int>(), elm["relaciones"].as<std::vector<int>>(), elm["tiempo"].as<double>(), elm["prioridad"].as<int>(), elm["cola"].as<std::vector<int>>());
            lista.push_back(maq);
        }
    }
    // Esta lista deve ir ordenada segun la prioridad (primero los de prioridad 1) que se establece en la configuracion
    std::sort(lista.begin(), lista.end(), [](const Maquina& a, const Maquina& b) {
        return a.get_prioridad() < b.get_prioridad(); 
    });
    return lista;
}


std::vector<Salida> Config::get_salidas(){
    std::vector<Salida> lista;
    const auto& elementos = config["modelo"]["entidades"];
    for (const auto& elm : elementos) {
        if (elm["tipo"].as<std::string>() == "salida"){
            Salida salida = Salida(elm["id"].as<int>(), elm["relaciones"].as<std::vector<int>>());
            lista.push_back(salida);
        }
    }
    return lista;
}