
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
            Entrada entrada = Entrada(elm["id"].as<int>(), elm["tiempo_generacion"].as<double>(), this->get_semilla(), generador_tiempo, generador_lote, elm["lambda"].as<double>(), 0.1);
            lista.push_back(entrada);
        }
    }
    return lista;
}

int Config::get_generador(std::string generador_str){
    if(!generador_str.compare("LINEAR_CONGRUENTIAL_ENGINE")) {
        return LINEAR_CONGRUENTIAL_ENGINE;
    } else if(!generador_str.compare("SUBTRACT_WITH_CARRY_ENGINE")){
        return SUBTRACT_WITH_CARRY_ENGINE;
    } else if(!generador_str.compare("MERSENNE_TWISTER_ENGINE")){
        return MERSENNE_TWISTER_ENGINE;
    }

    // Evita retornar un valor indefinido cuando la configuración no incluye un tipo soportado.
    return LINEAR_CONGRUENTIAL_ENGINE;
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