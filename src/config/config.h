

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "../entidades/maquina.h"
#include "../entidades/entrada.h"
#include "../experimento/experimento.h"

#ifndef CONFIG_H
#define CONFIG_H

    //https://github.com/jbeder/yaml-cpp
    //https://github.com/jbeder/yaml-cpp/blob/master/docs/Tutorial.md

class Config {
    private:
        YAML::Node config;

    public:
        explicit Config(const std::string& path) {
            config = YAML::LoadFile(path);
        }

        std::vector<Experimento> get_experimentos() {
            std::vector<Experimento> lista;
            const auto& elementos = config["simulacion"]["experimentos"];
            for (const auto& elm : elementos) {
                Experimento experimento = Experimento(elm["nombre"].as<std::string>(), elm["tiempo_simulacion"].as<double>());
                lista.push_back(experimento);
            }
            return lista;
        }


        std::vector<Entrada> get_entradas() {
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
                    Entrada entrada = Entrada(elm["id"].as<int>(), generador, elm["lambda"].as<double>());
                    lista.push_back(entrada);
                }
            }
            return lista;
        }



        std::vector<Maquina> get_maquinas() {
            std::vector<Maquina> lista;
            const auto& elemento = config["modelo"]["entidades"];
            for (const auto& elm : elemento) {
                if (elm["tipo"].as<std::string>() == "maquina"){
                    Maquina maq = Maquina(elm["id"].as<int>(), elm["trigger"].as<std::vector<int>>(), elm["tiempo"].as<double>(), elm["prioridad"].as<int>());
                    lista.push_back(maq);
                }
            }
            // Esta lista deve ir ordenada segun la prioridad (primero los de prioridad 1) que se establece en la configuracion
            std::sort(lista.begin(), lista.end(), [](const Maquina& a, const Maquina& b) {
                return a.get_prioridad() < b.get_prioridad(); 
            });
            return lista;
        }

};

#endif