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
    string entrada;
    cout << "Sistema de Manipulación de Genomas\n";
    cout << "Escriba 'ayuda' para ver l os comandos disponibles\n";

        while(true){
            cout << "$ ";
            getline(cin, entrada);

            size_t pos = entrada.find(' ');
            string comando = (pos == string::npos) ? entrada : entrada.substr(0, pos);
            string params = (pos == string::npos) ? "" : entrada.substr(pos + 1);

            // Convertir comando a minúsculas
            for (char &c : comando) c = tolower(c);

            procesarComando(comando, params);
        }
}

void LimpiarPantalla() {
    cout << "\033[2J\033[1;1H"; // Secuencia ANSI para limpiar y mover el cursor al inicio
}

void MostrarAyudaComando(std::string comando) {
    if (comando == "cargar") {
        cout << "Uso: cargar nombre_archivo.fa\n";
        cout << "Carga un archivo FASTA en memoria\n";
    }
    else if (comando == "listar_secuencias") {
        cout << "Uso: listar_secuencias\n";
        cout << "Muestra la lista las secuencias cargadas con su información básica\n";
    }
    else if (comando == "histograma") {
        cout << "Uso: histograma descripcion_secuencia\n";
        cout << "Muestra el histograma de una secuencia\n";
    }
    else if (comando == "es_subsecuencia") {
        cout << "Uso: es_subsecuencia subsecuencia\n";
        cout << "Determina si existe una subsecuencia en la secuencias cargadas en memoria\n";
    }
    else if (comando == "enmascarar") {
        cout << "Uso: enmascarar subsecuencia\n";
        cout << "Enmascara una subsecuencia dada por el usuario\n";
    }
    else if (comando == "guardar") {
        cout << "Uso: guardar nombre_archivo\n";
        cout << "Guarda en el archivo nombre_archivo las secuencias cargadas en memoria\n";
    }
    else if (comando == "codificar") {
        cout << "Uso: codificar nombre_archivo.fabin\n";
        cout << "El comando debe generar el archivo binario con la correspondiente codificación de Huffman\n";
    }
    else if (comando == "ruta_mas_corta") {
        cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n";

        cout << "El comando debe imprimir en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i ,j ] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x ,y ] de la misma matriz.\n";
    }
    else if (comando == "base_remota") {
        cout << "Uso: base_remota descripcion_secuencia i j\n";
        cout << "Para la base ubicada en la posición [i ,j ] de la matriz de la secuencia descripcion_secuencia, el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz\n";
    }
    else if (comando == "ayuda") {
        cout << "Uso: ayuda o ayuda <comando>\n";
        cout << "Muestra los comandos disponibles\n";
        cout << "Uso: ayuda <comando>\n";
        cout << "Muestra el uso del comando seleccionado\n";
    }
    else if (comando == "limpiar") {
            cout << "Uso: limpiar\n";
            cout << "Limpia la pantalla\n";
    }
    else if (comando == "salir") {
        cout << "Uso: salir\n";
        cout << "Termina la ejecución de la aplicación.\n";
        }
    else {
        cout << "Comando no reconocido." << endl;
    }
}

void ListarComandos(std::string parametros){
    if (parametros.empty()) {
            cout << "Comandos disponibles:\n";
            cout << "·cargar \n·listar_secuencias \n·histograma \n·es_subsecuencia \n";
            cout << "·enmascarar \n·guardar \n·codificar \n·decodificar \n";
            cout << "·ruta_mas_corta \n·base_remota \n·ayuda  \n·limpiar\n·salir \n";
            cout << "Ingrese 'ayuda <comando>' para obtener ayuda sobre un comando específico.\n";
        } else {
            mostrarAyudaComando(parametros);
    }
}

void Cargar(std::string Nombre){
    if (Nombre.empty()) {
        cout << "ERROR: Falta el nombre del archivo\n";
        return;
    }

    ifstream Cargar(Nombre);

    if(!Cargar.is_open()){
        cout << Nombre << "ERROR: el archivo no se encuentra o no puede leerse.\n";
        return;
    }

    Gestor.LimpiarSecuencias();
    string linea = "1";

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
    
    }
}