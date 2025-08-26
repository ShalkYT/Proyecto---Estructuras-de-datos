#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "GestorDeGenomas.h"
#include "Secuencia.h"
#include "Genomas.h"

void LimpiarPantalla();
void MostrarAyudaComando(std::string comando);
void ListarComandos(std::string parametros);
void ProcesarComando(std::string comando,std::string parametros);

GestorDeGenomas Gestor;

int main(){
    std::string entrada;
    std::cout << "Sistema de Manipulación de Genomas\n";
    std::cout << "Escriba 'ayuda' para ver l os comandos disponibles\n";

        while(true){
            std::cout << "$ ";
            getline(std::cin, entrada);

            size_t pos = entrada.find(' ');
            std::string comando = (pos == std::string::npos) ? entrada : entrada.substr(0, pos);
            std::string params = (pos == std::string::npos) ? "" : entrada.substr(pos + 1);

            // Convertir comando a minúsculas
            for (char &c : comando) c = tolower(c);

            ProcesarComando(comando, params);
        }
}

void LimpiarPantalla() {
    std::cout << "\033[2J\033[1;1H"; // Secuencia ANSI para limpiar y mover el cursor al inicio
}

void MostrarAyudaComando(std::string comando) {
    if (comando == "cargar") {
        std::cout << "Uso: cargar nombre_archivo.fa\n";
        std::cout << "Carga un archivo FASTA en memoria\n";
    }
    else if (comando == "listar_secuencias") {
        std::cout << "Uso: listar_secuencias\n";
        std::cout << "Muestra la lista las secuencias cargadas con su información básica\n";
    }
    else if (comando == "histograma") {
        std::cout << "Uso: histograma descripcion_secuencia\n";
        std::cout << "Muestra el histograma de una secuencia\n";
    }
    else if (comando == "es_subsecuencia") {
        std::cout << "Uso: es_subsecuencia subsecuencia\n";
        std::cout << "Determina si existe una subsecuencia en la secuencias cargadas en memoria\n";
    }
    else if (comando == "enmascarar") {
        std::cout << "Uso: enmascarar subsecuencia\n";
        std::cout << "Enmascara una subsecuencia dada por el usuario\n";
    }
    else if (comando == "guardar") {
        std::cout << "Uso: guardar nombre_archivo\n";
        std::cout << "Guarda en el archivo nombre_archivo las secuencias cargadas en memoria\n";
    }
    else if (comando == "codificar") {
        std::cout << "Uso: codificar nombre_archivo.fabin\n";
        std::cout << "El comando debe generar el archivo binario con la correspondiente codificación de Huffman\n";
    }
    else if (comando == "ruta_mas_corta") {
        std::cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
        std::cout << "El comando debe imprimir en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i ,j ] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x ,y ] de la misma matriz.\n";
    }
    else if (comando == "base_remota") {
        std::cout << "Uso: base_remota descripcion_secuencia i j\n";
        std::cout << "Para la base ubicada en la posición [i ,j ] de la matriz de la secuencia descripcion_secuencia, el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz\n";
    }
    else if (comando == "ayuda") {
        std::cout << "Uso: ayuda o ayuda <comando>\n";
        std::cout << "Muestra los comandos disponibles\n";
        std::cout << "Uso: ayuda <comando>\n";
        std::cout << "Muestra el uso del comando seleccionado\n";
    }
    else if (comando == "limpiar") {
            std::cout << "Uso: limpiar\n";
            std::cout << "Limpia la pantalla\n";
    }
    else if (comando == "salir") {
        std::cout << "Uso: salir\n";
        std::cout << "Termina la ejecución de la aplicación.\n";
        }
    else {
        std::cout << "Comando no reconocido.\n";
    }
}

void ListarComandos(std::string parametros){
    if (parametros.empty()) {
            std::cout << "Comandos disponibles:\n";
            std::cout << "·cargar \n·listar_secuencias \n·histograma \n·es_subsecuencia \n";
            std::cout << "·enmascarar \n·guardar \n·codificar \n·decodificar \n";
            std::cout << "·ruta_mas_corta \n·base_remota \n·ayuda  \n·limpiar\n·salir \n";
            std::cout << "Ingrese 'ayuda <comando>' para obtener ayuda sobre un comando específico.\n";
        } else {
            MostrarAyudaComando(parametros);
    }
}

void Cargar(std::string Nombre){
    if (Nombre.empty()) {
        std::cout << "ERROR: Falta el nombre del archivo\n";
        return;
    }

    std::ifstream Cargar(Nombre);

    if(!Cargar.is_open()){
        std::cout << Nombre << "ERROR: el archivo no se encuentra o no puede leerse.\n";
        return;
    }

    Gestor.LimpiarSecuencias();
    std::string linea = "1";

    while(true){
        Secuencia S;
        if(!linea.empty() && linea[0]=='>'){
            linea.erase(0,1);
            S.SetNombre(linea);
            
            while (getline(Cargar, linea) && (linea.empty() || linea[0] != '>')) {
            S.AñadirGenomas(linea);
            }

            Gestor.AñadirSecuencias(S);

        }else{
            getline(Cargar,linea);
        }
    
        if(Cargar.eof()){
            break;
        }
    }
}

void ProcesarComando(std::string comando,std::string parametros){
    if (comando == "ayuda") {
        ListarComandos(parametros);
    }
    else if (comando == "cargar") {
        Cargar(parametros);
    }
    else if (comando == "listar_secuencias") {
        
        Gestor.ListarSecuencias();
    }
    else if(comando == "histograma"){
        if(parametros.empty()){
            std::cout << "Error: Falta la descripción de la secuencia\n";
            return;
        }
        Gestor.Histograma(parametros);
    }

}