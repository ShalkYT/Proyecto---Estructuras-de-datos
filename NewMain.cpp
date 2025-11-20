#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include "Declaracion/GestorDeGenomas.h"
#include "Declaracion/Secuencia.h"
#include "Declaracion/Genomas.h"


// Limpia la pantalla de la consola usando secuencias ANSI.
void LimpiarPantalla();

// Muestra la ayuda detallada de un comando específico.
void MostrarAyudaComando(std::string comando);

// Lista todos los comandos disponibles o la ayuda de un comando en particular.
void ListarComandos(std::string parametros);

// Procesa un comando ingresado por el usuario junto con sus parámetros.
void ProcesarComando(std::string comando,std::string parametros);

// Objeto global del gestor de genomas.
GestorDeGenomas Gestor;

// Función principal que inicia el sistema interactivo de manipulación de genomas.
int main(){
    std::string entrada;  // Variable para almacenar la entrada completa del usuario.

    std::cout << "Sistema de Manipulación de Genomas\n";
    std::cout << "Escriba 'ayuda' para ver los comandos disponibles\n";

    // Bucle infinito que mantiene la aplicación activa hasta que el usuario escriba "salir".
    while(true){
        std::cout << "$ ";             // Prompt del sistema.
        getline(std::cin, entrada);    // Se lee toda la línea escrita por el usuario.

        // Buscar si hay un espacio para separar comando de parámetros.
        size_t pos = entrada.find(' ');

        // Si no hay espacio, todo es el comando. Si hay, se divide.
        std::string comando = (pos == std::string::npos) ? entrada : entrada.substr(0, pos);
        std::string params = (pos == std::string::npos) ? "" : entrada.substr(pos + 1);

        // Convertir el comando a minúsculas para evitar problemas de mayúsculas/minúsculas.
        for (char &c : comando) c = tolower(c);

        LimpiarPantalla();                 // Se limpia la pantalla antes de mostrar resultados.
        ProcesarComando(comando, params);  // Se ejecuta la acción asociada al comando.
    }
}

// Limpia la pantalla usando una secuencia ANSI.
void LimpiarPantalla() {
    std::cout << "\033[2J\033[1;1H";
}

// Muestra el uso y descripción de un comando específico.
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
        std::cout << "Genera un archivo binario con la codificación de Huffman\n";
    }
    else if (comando == "decodificar") {
        std::cout << "Uso: decodificar archivo_entrada.fabin archivo_salida.fa\n";
        std::cout << "Decodifica un archivo binario comprimido con Huffman y lo guarda como FASTA\n";
    }
    else if (comando == "ruta_mas_corta") {
        std::cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
        std::cout << "Imprime la secuencia de vértices que describen la ruta más corta entre dos posiciones en la matriz de la secuencia.\n";
    }
    else if (comando == "base_remota") {
        std::cout << "Uso: base_remota descripcion_secuencia i j\n";
        std::cout << "Busca la misma base más lejana a la posición dada dentro de la matriz.\n";
    }
    else if (comando == "ayuda") {
        std::cout << "Uso: ayuda o ayuda <comando>\n";
        std::cout << "Muestra los comandos disponibles o la ayuda de un comando específico\n";
    }
    else if (comando == "salir") {
        std::cout << "Uso: salir\n";
        std::cout << "Termina la ejecución de la aplicación.\n";
    }
    else {
        std::cout << "Comando no reconocido.\n";
    }
}

// Lista todos los comandos o muestra la ayuda de uno en específico.
void ListarComandos(std::string parametros){
    if (parametros.empty()) {
        std::cout << "Comandos disponibles:\n";
        std::cout << "·cargar \n·listar_secuencias \n·histograma \n·es_subsecuencia \n";
        std::cout << "·enmascarar \n·guardar \n·codificar \n·decodificar \n";
        std::cout << "·ruta_mas_corta \n·base_remota \n";
        std::cout << "·ayuda \n·salir \n";
        std::cout << "Ingrese 'ayuda <comando>' para obtener ayuda sobre un comando específico.\n";
    } else {
        MostrarAyudaComando(parametros);
    }
}

// Procesa el comando ingresado y ejecuta la acción correspondiente.
void ProcesarComando(std::string comando, std::string parametros){
    if (comando == "ayuda") {
        ListarComandos(parametros);
    }
    else if (comando == "cargar") {
        Gestor.CargarFASTA(parametros);  
    }
    else if (comando == "guardar") {
        Gestor.GuardarFASTA(parametros); 
    }
    else if (comando == "codificar") {
        Gestor.CodificarHuffman(parametros);  
    }
    else if (comando == "decodificar") {
        Gestor.DecodificarHuffman(parametros);

    }
    else if (comando == "listar_secuencias") {
        Gestor.ListarSecuencias();
    }
    else if(comando == "histograma"){
        if(parametros.empty()){
            std::cout << "ERROR: Falta la descripción de la secuencia\n";
            return;
        }
        Gestor.Histograma(parametros);
    }
    else if(comando == "es_subsecuencia"){
        int temp = Gestor.Cantidad_Subsecuencias(parametros);
        if(temp == 0){
            std::cout << "La subsecuencia no existe\n";
        } else {
            std::cout << "La subsecuencia se repite " << temp << " veces\n";
        }
    }
    else if(comando == "enmascarar"){
        int temp = Gestor.Enmascarar_Subsecuencias(parametros);
        if(temp == 0){
            std::cout << "La subsecuencia no existe\n";
        } else {
            std::cout << temp << " subsecuencias enmascaradas\n";
        }
    }
    else if(comando == "ruta_mas_corta"){
        Gestor.ruta_mas_corta(parametros);
        
        }
        else if(comando == "base_remota"){
            std::cout<<"Implementar funcion de base remota\n";
        }
        else if(comando == "salir"){
            exit(0);
        }
        else {
            std::cout << "Comando no reconocido\n";
        }
}
