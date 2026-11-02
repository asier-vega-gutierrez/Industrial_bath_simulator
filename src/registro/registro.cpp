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
    std::ofstream archivo(RUTA_REGISTRO, std::ios::out); 
    if (archivo.is_open()) {
        archivo << "";
        archivo.close();
    }
}

void Registro::print_iniciar() {
    vaciar();
    std::string msg = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    msg += std::string(this->cabecera_informacion) + "La simulacion de este experimento a comenzado\n";
    this->escribir(msg);
}

void Registro::print_estado_sistema(Evento ev) {
    std::string msg = "---------------------------------------------------------\n";
    msg += std::string(this->cabecera_informacion) + "Nueva iteracion de simulacion \n";
    msg += std::string(this->cabecera_informacion) + "El evento actual es: " + 
           std::to_string(ev.get_origen()) + " " + 
           std::to_string(ev.get_tipo()) + " " + 
           std::to_string(ev.get_tiempo()) + " \n";
    this->escribir(msg);
}

void Registro::print_cola_eventos(ColaEventos cola) {
    ColaEventos copia = cola;
    std::string msg = std::string(this->cabecera_informacion) + "Lista de eventos: \n";
    while (!copia.empty()) {
        Evento ev = copia.top();
        msg += "> origen: " + std::to_string(ev.get_origen()) + 
               " tipo: " + std::to_string(ev.get_tipo()) + 
               " tiempo: " + std::to_string(ev.get_tiempo()) + "\n";
        copia.pop();
    }
    this->escribir(msg);
}

void Registro::print_finalizar() {
    std::string msg = std::string(this->cabecera_informacion) + "La simulacion de este experimento a terminado\n";
    msg += "++++++++++++++++++++++++++++++++++++++++++++++++\n";
    this->escribir(msg);
}

void Registro::print_entidad_estado(int id) {
    std::string msg = std::string(this->cabecera_accion) + "Maquina " + std::to_string(id) + " actualiza su estado\n";
    this->escribir(msg);
}   

void Registro::print_entidad_generacion(int id) {
    std::string msg = std::string(this->cabecera_accion) + "Maquina " + std::to_string(id) + " a generado un evento\n";
    this->escribir(msg);
}   

void Registro::print_cola_llena(int id) {
    std::string msg = std::string(this->cabecera_informacion) + "Cola de maquina " + std::to_string(id) + " llena \n";
    this->escribir(msg);
}

void Registro::print_anadir_cola(int id, int actual) {
    std::string msg = std::string(this->cabecera_accion) + "Evento anadido a la cola de maquina " + 
                      std::to_string(id) + ", cola con " + std::to_string(actual) + " eventos \n";
    this->escribir(msg);
}

void Registro::print_anadir_denuevo_cola(int id, int actual) {
    std::string msg = std::string(this->cabecera_accion) + "Evento anadido de nuevo a la cola de maquina " + 
                      std::to_string(id) + ", cola con " + std::to_string(actual) + " eventos \n";
    this->escribir(msg);
}

void Registro::print_elminar_cola(int id, int actual) {
    std::string msg = std::string(this->cabecera_accion) + "Evento eliminado de la cola de maquina " + 
                      std::to_string(id) + ", cola con " + std::to_string(actual) + " eventos \n";
    this->escribir(msg);
}

void Registro::print_evento_salida() {
    std::string msg = std::string(this->cabecera_informacion) + "Evento de salida detectado \n";
    this->escribir(msg);
}

void Registro::print_resultado_iteracion(bool flag) {
    std::string msg = "";
    if (flag) {
        msg = std::string(this->cabecera_resultado) + "Evento actual procesado \n";
    } else {
        msg = std::string(this->cabecera_resultado) + "Evento actual NO procesado \n";
    }
    this->escribir(msg);
}