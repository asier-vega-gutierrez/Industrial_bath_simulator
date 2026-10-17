#include "../entidades/maquina.h"
#include "../entidades/entrada.h"
#include "../experimento/experimento.h"

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


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

        std::vector<Experimento> get_experimentos();
        std::vector<Entrada> get_entradas();
        std::vector<Maquina> get_maquinas();

};

#endif