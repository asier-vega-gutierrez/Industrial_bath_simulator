
#include "config.h"

double Config::get_tiempo_simulacion() {
    return config["simulacion"]["tiempo_simulacion"].as<double>();
}


std::vector<Entrada> Config::get_entradas() {
    std::vector<Entrada> lista;
    const auto& elementos = config["modelo"]["entidades"];
    for (const auto& elm : elementos) {
        if (elm["tipo"].as<std::string>() == "entrada"){
            int generador = 1;
            std::string generador_str = elm["generador"].as<std::string>();
            if(!generador_str.compare("LINEAR_CONGRUENTIAL_ENGINE")) {
                generador = LINEAR_CONGRUENTIAL_ENGINE;
            } else if(!generador_str.compare("SUBTRACT_WITH_CARRY_ENGINE")){
                generador = SUBTRACT_WITH_CARRY_ENGINE;
            } else if(!generador_str.compare("MERSENNE_TWISTER_ENGINE")){
                generador = MERSENNE_TWISTER_ENGINE;
            }
            Entrada entrada = Entrada(elm["id"].as<int>(), generador, elm["lambda"].as<double>(), elm["tiempo_generacion"].as<double>());
            lista.push_back(entrada);
        }
    }
    return lista;
}



std::vector<Maquina> Config::get_maquinas() {
    std::vector<Maquina> lista;
    const auto& elemento = config["modelo"]["entidades"];
    for (const auto& elm : elemento) {
        if (elm["tipo"].as<std::string>() == "maquina"){
            Maquina maq = Maquina(elm["id"].as<int>(), elm["relaciones"].as<std::vector<int>>(), elm["tiempo"].as<double>(), elm["prioridad"].as<int>());
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