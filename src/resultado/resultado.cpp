
#include "resultado.h"

// Almacena la lista de eventos original
void Resultado::almacenar_inicial(ColaEventos lista_eventos){
    auto copia = lista_eventos;
    while (!copia.empty()) {
        this->eventos_iniciales.push_back(copia.top());
        copia.pop();
    }
}

// Almacena informacion al final de cada iteracion
void Resultado::almacenar_iteracion(bool evento_procesado, Evento evento){
    // Se almacena el evento en la lista completa
    this->eventos_lista_completa.push_back(evento);
    // Se almacen si el evento a sido procesado o se ha descartado
    if (evento_procesado) {
        this->eventos_procesados.push_back(evento);
    } else if (!evento_procesado){
        this->eventos_sinprocesar.push_back(evento);
    }
    // Se escribe un aviso para que esta accion quede registrada
    std::string msg = "";
    if (evento_procesado) {
        msg = "--{ Evento actual procesado \n";
    } else {
        msg = "--{ Evento actual NO procesado \n";
    }
    registro.escribir(msg);
}

// Almacena la lista de eventos final
void Resultado::almacenar_final(ColaEventos lista_eventos){
    auto copia = lista_eventos;
    while (!copia.empty()) {
        this->eventos_finales.push_back(copia.top());
        //Tambien se guardan en la lista completa
        this->eventos_lista_completa.push_back(copia.top());
        copia.pop();
    }

}

void Resultado::procesar(){

    informe.print_iniciar_informe();
    std::string msg = "";

    // por comodidad se ordena segun id las maquinas que estan ordenadas por prioridad
    std::vector<Maquina> lista_maquinas_sortid = this->lista_maquinas;
    std::sort(lista_maquinas_sortid.begin(), lista_maquinas_sortid.end(), [](const Maquina& a, const Maquina& b) {
        return a.get_id() < b.get_id(); 
    });

    // INFORMACION SOBRE LA SIMULACION
    informe.escribir("\nINFORMACION SOBRE LA SIMULACION: \n");

    // Las semillas utilizadas para cada entrada
    msg = "";
    for(const Entrada& entrada : this->lista_entradas){
        // printf("La semilla de la entrada %d, es %u \n", entrada.get_id(), entrada.get_semilla());
        msg += "La semilla de la entrada " + std::to_string(entrada.get_id()) + " es " + std::to_string(entrada.get_semilla()) + " \n";
    }
    informe.escribir(msg);

    // INFORMACION SOBRE LOS EVENTOS
    informe.escribir("\nINFORMACION SOBRE LOS EVENTOS: \n");

    int count_eventos_ext = count_vector_tipo_evento(eventos_lista_completa, EXTERNO);
    int count_eventos_finales_ext = count_vector_tipo_evento(eventos_finales, EXTERNO);
    int count_eventos_sinprocesar_ext = count_vector_tipo_evento(eventos_sinprocesar, EXTERNO);
    // Porcentaje de los eventos EXTERNOs procesados y no 
    double eesp = (double)count_eventos_sinprocesar_ext / (count_eventos_ext - count_eventos_finales_ext);
    msg = "";
    msg += "Cantidad de eventos EXTERNOs procesados: " + std::to_string(count_eventos_ext - count_eventos_finales_ext - count_eventos_sinprocesar_ext) + "\n";
    msg += "Cantidad de eventos EXTERNOs sin procesar: " + std::to_string(count_eventos_sinprocesar_ext) + "\n";
    msg += "Eventos EXTERNOs sin procesar: " + std::to_string(eesp * 100.0) + "\n";
    msg += "Eventos EXTERNOs procesados: " + std::to_string((1-eesp) * 100.0) + "\n";
    informe.escribir(msg);

    int count_eventos_int = count_vector_tipo_evento(eventos_lista_completa, INTERNO);
    int count_eventos_finales_int = count_vector_tipo_evento(eventos_finales, INTERNO);
    int count_eventos_sinprocesar_int = count_vector_tipo_evento(eventos_sinprocesar, INTERNO);
    // Porcentaje de los eventos INTERNOS procesados y no (TODO que pasa con los de tipo 3 ????)
    double eisp = (double)count_eventos_sinprocesar_int / (count_eventos_int - count_eventos_finales_int);
    msg = "";
    msg += "Cantidad de eventos INTERNOs procesados: " + std::to_string(count_eventos_int - count_eventos_finales_int - count_eventos_sinprocesar_int) + "\n";
    msg += "Cantidad de eventos INTERNOs sin procesar: " + std::to_string(count_eventos_sinprocesar_int) + "\n";
    msg += "Eventos INTERNOs sin procesar: " + std::to_string(eisp * 100.0) + "\n";
    msg += "Eventos INTERNOs procesados: " + std::to_string((1-eisp) * 100.0) + "\n";
    informe.escribir(msg);

    // INFORMACION SOBRE LAS MAQUINAS
    informe.escribir("\nINFORMACION SOBRE LAS MAQUINAS: \n");

    // Eficiencia de las maquina
    msg = "";
    for(Maquina maquina : lista_maquinas_sortid){ 
        double em = (maquina.get_tiempo_produciendo()/this->tiempo_simulacion) * 100.0;
        msg += "Eficiencia de la maquina "+std::to_string(maquina.get_id())+" es: "+std::to_string(em)+" % \n";
        msg += "El timepo que ha estado parada la mquina " + std::to_string(maquina.get_id()) + " es: " + std::to_string(maquina.get_tiempo_sinproducir()) + " minutos \n";
    }
    informe.escribir(msg);

    // Maximo y minimo historico de la cola
    msg = "";
    for(const Maquina& maquina : lista_maquinas_sortid){
        // for(const Cola& cola : maquina.get_colas()){
        for(int i = 0; i < maquina.get_colas().size(); i++){
            msg += "Cantidad de eventos maxima de la maquina " + std::to_string(maquina.get_id()) + " para su cola de relacion " + std::to_string(maquina.get_relaciones()[i]) + " es de: " + std::to_string(maquina.get_colas()[i].get_max_historico()) + " \n";
            msg += "Cantidad de eventos minima de la maquina " + std::to_string(maquina.get_id()) + " para su cola de relacion " + std::to_string(maquina.get_relaciones()[i]) + " es de: " + std::to_string(maquina.get_colas()[i].get_min_historico()) + " \n";      
        }
    }
    informe.escribir(msg);

    // INFORMACION SOBRE LA SALIDA
    informe.escribir("\nINFORMACION SOBRE LA SALIDA: \n");
    
    // Cantidad de eventos de salida
    msg = "";
    for(const Salida& salida : this->lista_salidas){
        if (salida.get_count_eventos() != 0){
            msg += "Cantidad de eventos de la salida " + std::to_string(salida.get_id()) + " es " + std::to_string(salida.get_count_eventos()) + " son: \n";
            for(Evento ev : salida.get_eventos()){
                msg += "> origen: " + std::to_string(ev.get_origen()) + " tipo: " + std::to_string(ev.get_tipo()) + " tiempo: " + std::to_string(ev.get_tiempo()) + "\n";
            }
        }
    }
    informe.escribir(msg);


}

int Resultado::count_vector_tipo_evento(std::vector<Evento> lista,int tipo){
    int count = 0;
    for (Evento evento : lista){
        if(evento.get_tipo() == tipo){
            count += 1;
        }
    }
    return count;
}