#include "registro.h"

// Método auxiliar privado para escribir en consola y en el archivo compartido
void Registro::escribir(const std::string& mensaje) {
    // Imprime en la consola estándar
    std::cout << mensaje;

    // Abre, escribe y cierra el archivo compartido en modo "append" (añade al final)
    // Esto permite que múltiples instancias escriban de forma segura.
    std::ofstream archivo(this->ruta, std::ios::out | std::ios::app);
    if (archivo.is_open()) {
        archivo << mensaje;
        archivo.close();
    }
}

void Registro::vaciar(){
    std::cout << "";
    // Abrir sin std::ios::app vacía el archivo automáticamente al arrancar la simulación
    std::ofstream archivo(this->ruta, std::ios::out); 
    if (archivo.is_open()) {
        archivo << "";
        archivo.close();
    }
}

void Registro::print_iniciar_simulacion() {
    vaciar();
    std::string msg = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    msg += "--- La simulacion de este experimento a comenzado\n";
    this->escribir(msg);
}

void Registro::print_iniciar_informe() {
    vaciar();
    std::string msg = "";
    msg += "----- INFORME DE SIMULACION -----\n";
    this->escribir(msg);
}

void Registro::print_cola_eventos(ColaEventos cola) {
    ColaEventos copia = cola;
    std::string msg = "--- Lista de eventos: \n";
    while (!copia.empty()) {
        Evento ev = copia.top();
        msg += "> origen: " + std::to_string(ev.get_origen()) + " tipo: " + std::to_string(ev.get_tipo()) + " tiempo: " + std::to_string(ev.get_tiempo()) + "\n";
        copia.pop();
    }
    this->escribir(msg);
}