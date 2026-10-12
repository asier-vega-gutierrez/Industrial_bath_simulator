#ifndef YAML_READER_H
#define YAML_READER_H

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "../entidades/maquina.h"

class Config {
    private:
        YAML::Node config;

    public:
        explicit Config(const std::string& path) {
            config = YAML::LoadFile(path);
        }

        // std::vector<Maquina> get_maquinas() {
        //     std::vector<Maquina> lista;
        //     const auto& entidades = config["modelo"]["entidades"];
        //     for (const auto& ent : entidades) {
        //         if (ent["tipo"].as<std::string>() == "maquina"){
        //             Maquina maq = Maquina(ent["id"].as<int>(), ent["trigger"].as<std::vector<int>>());
        //             lista.push_back(maq);
        //         }
        //     }
        //     return lista;
        // }

        std::vector<Maquina> get_maquinas() {
            std::vector<Maquina> lista;
            const auto& entidades = config["modelo"]["entidades"];
            for (const auto& ent : entidades) {
                if (ent["tipo"].as<std::string>() == "maquina"){
                    Maquina maq = Maquina(ent["id"].as<int>(), ent["trigger"].as<std::vector<int>>());
                    lista.push_back(maq);
                }
            }
            return lista;
        }

};

#endif