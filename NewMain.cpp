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
        std::cout << "·enmascarar \n·guardar \n";
        std::cout << "·ayuda \n·salir \n";
        std::cout << "Ingrese 'ayuda <comando>' para obtener ayuda sobre un comando específico.\n";
    } else {
        MostrarAyudaComando(parametros);
    }
}

// Carga un archivo FASTA en memoria y guarda las secuencias en el gestor.
void Cargar(std::string Nombre){
    if (Nombre.empty()) {
        std::cout << "ERROR: Falta el nombre del archivo\n";
        return;
    }
    std::string direccion = "ArchivosPrueba/" + Nombre;
    std::ifstream Cargar(direccion);  // Se abre el archivo en modo lectura.
    std::cout<< direccion;

    if(!Cargar.is_open()){
        std::cout<< "ERROR: el archivo \"" << Nombre <<"\" no se encuentra o no puede leerse.\n";
        return;
    }

    Gestor.LimpiarSecuencias(); // Se eliminan las secuencias previas.
    std::string NombreSecuencia;
    char Aux = ' ';              // Variable auxiliar para leer caracteres.
    std::string linea = " ";     // Línea actual que se analiza.

    // Se procesa el archivo de forma secuencial.
    while (true) {
        Secuencia S;              // Objeto que almacenará cada secuencia.
        std::deque<char> Genomas; // Contenedor para los caracteres de cada genoma.

        // Si la línea comienza con '>', significa que es el nombre de la secuencia.
        if (!linea.empty() && linea[0] == '>') {
            linea.erase(0, 1);    
            S.SetNombre(linea);

            // Se leen los caracteres de la secuencia hasta encontrar otra cabecera o el fin del archivo.
            while (Cargar.get(Aux)) {
                if (Aux == '>') {       // Si se encuentra otra cabecera, se retrocede y se detiene.
                    Cargar.putback(Aux);
                    break;
                }
                if (Aux == '\n' || Aux == '\r') { // Si es salto de línea, se guarda lo acumulado.
                    S.AñadirGenomas(Genomas);
                    Genomas.clear();
                    continue;      
                }
                Genomas.push_back(Aux); // Se añade cada base de la secuencia.
            }

            Gestor.AñadirSecuencias(S); // Se guarda la secuencia completa en el gestor.

        } else {
            // Si no es una cabecera, se intenta leer una nueva línea.
            if (!std::getline(Cargar, linea)) {
                break; 
            }
        }

        if (Cargar.eof()) { // Si se llegó al final del archivo, se detiene.
            break;
        }
    }

    // Resumen de cuántas secuencias se cargaron.
    long long temp = (Gestor.getSecuencias()).size();

    if(temp == 0){
        std::cout << Nombre <<" no contiene ninguna secuencia.\n";
    }
    else if(temp == 1){
        std::cout <<" 1 secuencia cargada correctamente desde " << Nombre << "\n";
    }else{
        std::cout <<" "<< temp <<" secuencias cargadas correctamente desde " << Nombre << "\n";
    }

    Cargar.close(); // Se cierra el archivo.
}

// Guarda las secuencias cargadas en memoria en un archivo de salida.
void Guardar(std::string Nombre){
    if (Nombre.empty()) {
        std::cout << "ERROR: Falta el nombre del archivo\n";
        return;
    }

    if((Gestor.getSecuencias()).empty()){
        std::cout << "ERROR: no hay secuencias cargadas en memoria\n";
        return;
    }

    std::ofstream Guardar(Nombre); // Abrir archivo en modo escritura.

    if(!Guardar.is_open()){
        std::cout << "ERROR guardando en el archivo " << Nombre << "\n";
        return;
    }

    // Obtener todas las secuencias cargadas.
    std::vector<Secuencia> temp = Gestor.getSecuencias();

    // Recorrer cada secuencia cargada.
    for(std::vector<Secuencia>::iterator teit = temp.begin(); teit != temp.end(); teit++){
        Guardar << ">" << teit->GetNombre() << "\n"; // Imprimir cabecera con nombre.

        // Obtener los genomas de cada secuencia.
        std::vector<Genomas> sub_temp = teit->GetGenomas();
        for(std::vector<Genomas>::iterator suit = sub_temp.begin(); suit != sub_temp.end() ; suit++){
            std::deque<char> Genomas = suit->GetGenomas();
            std::deque<char>::iterator itchar;

            // Recorrer cada carácter de los genomas y guardarlo en el archivo.
            for(itchar = Genomas.begin() ;itchar != Genomas.end(); itchar++){
                Guardar << *(itchar);
            }
            Guardar << "\n"; // Fin de línea para cada genoma.
        }
    }

    std::cout << "Las secuencias han sido guardadas en " << Nombre << "\n";
    Guardar.close();
}

// Procesa el comando ingresado y ejecuta la acción correspondiente.
void ProcesarComando(std::string comando,std::string parametros){
    int temp;

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
            std::cout << "ERROR: Falta la descripción de la secuencia\n";
            return;
        }
        Gestor.Histograma(parametros);
    }
    else if(comando == "es_subsecuencia"){
        if(((Gestor.getSecuencias()).size()) == 0){
            std::cout << "ERROR: No hay secuencias cargadas.\n";
        }else{
            temp = Gestor.Cantidad_Subsecuencias(parametros);
            if(temp == 0){
                std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
            }else{
                std::cout << "La subsecuencia dada se repite " << temp << " veces dentro de las secuencias cargadas en memoria\n";
            }
        }
    }
    else if(comando == "enmascarar"){
        if(((Gestor.getSecuencias()).size()) == 0){
            std::cout << "No hay secuencias cargadas.\n";
        }else{
            temp = Gestor.Enmascarar_Subsecuencias(parametros);
            if(temp == 0){
                std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por lo tanto no se enmascaro nada.\n";
            }else{
                std::cout<< temp << " subsecuencias han sido enmascaradas de las secuencias cargadas en memoria\n";
            }
        }
    }
    else if(comando == "guardar") {
        Guardar(parametros);
    }
    else if(comando == "salir"){
        exit(0);
    }
    else{
        std::cout << "Comando no reconocido\n";
    }
}
