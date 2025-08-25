#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Variables de estado del sistema
bool secuenciasCargadas = false;
string nombreArchivoActual = "";
int justificacion = 0; // Ancho de línea simulado
string** matriz = nullptr;
int secuencias;
int* subsecuencias = nullptr;
int* tamaños = nullptr;

#include <cstdlib>

//Funcion para manejar matriz


//Función que limpia la pantalla
void limpiarPantalla() {
    cout << "\033[2J\033[1;1H"; // Secuencia ANSI para limpiar y mover el cursor al inicio
}

//Función que espera a que el usuario presione Enter para limpiar la pantalla

// Función auxiliar para verificar archivos
bool archivoExiste(const string& nombre) {
    ifstream archivo(nombre);
    return archivo.good();
}

// Función para mostrar ayuda específica de cada comando
void mostrarAyudaComando(const string& comando) {
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
    else if (comando == "decodificar") {
        cout << "Uso: decodificar nombre_archivo.fabin\n";
        cout << "El comando debe cargar en memoria las secuencias contenidas en el archivo binario nombre_archivo.fabin\n";
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

void procesarComando(const string& comando, const string& parametros) {
    if (comando == "ayuda") {
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
    else if (comando == "cargar") {
        if (parametros.empty()) {
            cout << "Error: Falta el nombre del archivo\n";
            return;
        }

        ifstream Cargar(parametros);

        if(!Cargar.is_open()){
            cout << parametros << " no se encuentra o no puede leerse.\n";
            return;
        }

        string linea;
        secuencias = 0;

        while(getline(Cargar,linea)){
            if(!linea.empty() && linea[0]=='>'){
                secuencias++;
            }
        }

        subsecuencias = new int[secuencias]();
        tamaños = new int[secuencias]();
        int iterador = 0;

        linea = "";
        Cargar.clear();
        Cargar.seekg(0);
        bool reutilizar = false, primeralinea = true;

        while (true) {
            if(!reutilizar){
                if (!getline(Cargar, linea)) break;
            }
            reutilizar = false;

            if (!linea.empty() && linea[0] == '>') {
                primeralinea = true;
                while (getline(Cargar, linea) && (!linea.empty() && linea[0] != '>')) {
                    if(primeralinea) {
                        tamaños[iterador] = linea.size();
                        primeralinea = false;
                        subsecuencias[iterador]++;
                    }
                    subsecuencias[iterador]++;
                }
                iterador++;
                if (!linea.empty() && linea[0] == '>') {
                    reutilizar = true; // guardamos para procesar en la siguiente vuelta
                }
            }
        }

        matriz = new string*[secuencias];
        for(int i = 0; i<secuencias; i++){
            matriz[i] = new string[subsecuencias[i]];
        }

        // Volver al inicio del archivo para llenarlo
        Cargar.clear();
        Cargar.seekg(0);

        iterador = 0;
            int subIterador = 0;

        while (getline(Cargar, linea)) {
            if (!linea.empty() && linea[0] == '>') {
                // Nueva secuencia
                matriz[iterador][0] = linea;
                subIterador = 1; // Reiniciamos contador de subsecuencias para esta fila
            }
            else if (!linea.empty()) {
                // Guardamos la subsecuencia en la matriz
                matriz[iterador][subIterador] = linea;
                subIterador++;

                // Si llegamos al final de subsecuencias de esta secuencia, pasamos a la siguiente
                if (subIterador >= subsecuencias[iterador]) {
                    iterador++;
                }
            }
        }     

        secuenciasCargadas = true;
        nombreArchivoActual = parametros;
        justificacion = 50; // Valor simulado
        cout << secuencias <<" secuencias cargadas correctamente desde " << parametros << "\n";
    }
    else if (comando == "listar_secuencias") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        cout << "Hay " << secuencias <<" secuencias cargadas en memoria:\n";
        int bases ;
        for(int i = 0; i <secuencias;i++){
            bases = 0;
            for(int j = 1; j < subsecuencias[i]; j++){
                bases+=matriz[i][j].size();
            }
            cout << matriz[i][0] << " contiene " << bases <<" bases.\n";
        }

    }
    else if (comando == "histograma") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        if (parametros.empty()) {
            cout << "Error: Falta la descripción de la secuencia\n";
            return;
        }

        bool existe = false;
        int subsecuenciacorrecta = 0;
        for(int i = 0; i<secuencias;i++){
            if(parametros==matriz[i][0]){
                existe = true;
                subsecuenciacorrecta = i;
                break;
            }
        }

        int A = 0, T = 0, C = 0, G = 0, X = 0;

        if(existe){
            for(int i=1;i<subsecuencias[subsecuenciacorrecta];i++){
                for(char base: matriz[subsecuenciacorrecta][i]){
                    switch(base){
                        case 'A':
                            A++;
                        break;
                        case 'T':
                            T++;
                        break;
                        case 'C':
                            C++;
                        break;
                        case 'G':
                            G++;
                        break;
                        default:
                            X++;
                    }
                }
            }
            cout << "La secuencia " << parametros << " contiene: \nA: " << A << "\nT: " << T << "\nC: " << C << " \nG: " << G <<endl;
        }else{
            cout << "La secuencia " << parametros << "no esta en la informacion cargada\n";
        }


    }
    else if (comando == "es_subsecuencia") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        if (parametros.empty()) {
            cout << "Error: Falta la subsecuencia a buscar\n";
            return;
        }

        size_t pos;
        int contador = 0;

        for(int i = 0; i< secuencias;i++){
            for(int j = 1; j< subsecuencias[i] ; j++){
                pos = matriz[i][j].find(parametros);

                while (pos != string::npos) {
                    contador++;
                    pos = matriz[i][j].find(parametros, pos + parametros.length());
                }
            }
        }

        if(contador == 0){
            cout << "La subsecuencia " << parametros << "no es subsecuencia de las secuencias cargadas\n";
        }else{
            cout << "La subsecuencia dada se repite " << contador <<" veces dentro de las secuencias cargadas en memoria.\n";
        }
    }
    else if (comando == "enmascarar") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        if (parametros.empty()) {
            cout << "Error: Falta la subsecuencia a enmascarar\n";
            return;
        }

        int contador = 0;
        for (int i = 0; i < secuencias; i++) {
            for (int j = 1; j < subsecuencias[i]; j++) {
                size_t pos = matriz[i][j].find(parametros);

                while (pos != string::npos) {
                    // Reemplaza la coincidencia encontrada por "X"
                    contador++;
                    matriz[i][j].replace(pos, parametros.length(), "X");

                    // Busca la siguiente coincidencia después de la recién reemplazada
                    pos = matriz[i][j].find(parametros, pos + 1);
                }
            }
        }

        cout << contador <<"3 subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";


    for (int i = 0; i < secuencias; i++) {
        for (int j = 0; j < subsecuencias[i]; j++) {
            cout << matriz[i][j] << "\t"; // tabulación para separar columnas
        }
        cout << "\n";
    }

    }
    else if (comando == "guardar") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        if (parametros.empty()) {
            cout << "Error: Falta el nombre del archivo de destino\n";
            return;
        }
        cout << "Las secuencias han sido guardadas en " << parametros << "\n";
    }
    else if (comando == "codificar") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        if (parametros.empty()) {
            cout << "Error: Falta el nombre del archivo .fabin\n";
            return;
        }
        cout << "Secuencias codificadas y almacenadas en " << parametros << "\n";
    }
    else if (comando == "ruta_mas_corta") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        // Validar parámetros (simplificado)
        cout << "Para la secuencia " << nombreArchivoActual << ", la ruta más corta es: ...\n";
        cout << "El costo total de la ruta es: 5.2\n";
    }
    else if (comando == "base_remota") {
        if (!secuenciasCargadas) {
            cout << "No hay secuencias cargadas en memoria.\n";
            return;
        }
        // Validar parámetros (simplificado)
        cout << "Para la secuencia " << nombreArchivoActual << ", la base remota está en [10,15]\n";
        cout << "El costo total de la ruta es: 7.8\n";
    }
    else if (comando == "limpiar") {
        limpiarPantalla();
        cout << "Sistema de Manipulación de Genomas\n";
        cout << "Escriba 'ayuda' para ver l os comandos disponibles\n";
    }
    else if (comando == "salir") {
        exit(0);
    }
    else {
        cout << "Comando no reconocido. Escriba 'ayuda' para ver la lista de comandos.\n";
    }
}

int main() {
    string entrada;
    cout << "Sistema de Manipulación de Genomas\n";
    cout << "Escriba 'ayuda' para ver l os comandos disponibles\n";

        while (true) {
        cout << "$ ";
        getline(cin, entrada);

        size_t pos = entrada.find(' ');
        string comando = (pos == string::npos) ? entrada : entrada.substr(0, pos);
        string params = (pos == string::npos) ? "" : entrada.substr(pos + 1);

        // Convertir comando a minúsculas
        for (char &c : comando) c = tolower(c);

        procesarComando(comando, params);
    }

    return 0;
}