// ===================================================================================
// File:                   GestorDeGenomas.cpp
// Autor:                  Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:       2025-09-03
// Descripción:            Implementación de los métodos de la clase GestorDeGenomas.
//                         Esta clase administra múltiples objetos de tipo Secuencia,
//                         permitiendo añadir, limpiar, listar, generar histogramas,
//                         y realizar operaciones sobre subsecuencias.
// ===================================================================================

#include "GestorDeGenomas.h"
#include "ArbolHuffman/arbolH.h"
#include <iostream>
#include <fstream>

bool GestorDeGenomas::CargarFASTA(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    
    if(!archivo.is_open()){
        std::cout << "ERROR: el archivo \"" << nombreArchivo << "\" no se encuentra o no puede leerse.\n";
        return false;
    }

    LimpiarSecuencias(); // Limpiar secuencias anteriores
    
    std::string linea;
    int secuenciasDescartadas = 0;

    while (std::getline(archivo, linea)) {
        if (!linea.empty() && linea[0] == '>') {
            std::string nombreSecuencia = linea.substr(1);
            std::vector<std::string> lineasSecuencia;
            
            // Leer todas las líneas de esta secuencia
            while (std::getline(archivo, linea) && !linea.empty() && linea[0] != '>') {
                std::string lineaLimpia;
                for (char c : linea) {
                    if (c != '\r' && c != '\n' && c != ' ' && c != '\t') {
                        lineaLimpia += c;
                    }
                }
                if (!lineaLimpia.empty()) {
                    lineasSecuencia.push_back(lineaLimpia);
                }
            }

            // Validar ancho consistente
            bool anchoConsistente = true;
            if (!lineasSecuencia.empty()) {
                size_t anchoReferencia = lineasSecuencia[0].length();
                for (const std::string& lineaSeq : lineasSecuencia) {
                    if (lineaSeq.length() != anchoReferencia) {
                        anchoConsistente = false;
                        break;
                    }
                }
            }

            // Solo añadir si tiene ancho consistente
            if (anchoConsistente && !lineasSecuencia.empty()) {
                Secuencia S;
                S.SetNombre(nombreSecuencia);
                
                for (const std::string& lineaSeq : lineasSecuencia) {
                    std::deque<char> genomas;
                    for (char c : lineaSeq) {
                        genomas.push_back(c);
                    }
                    S.AñadirGenomas(genomas);
                }
                
                AñadirSecuencias(S);
            } else {
                secuenciasDescartadas++;
                std::cout << "ADVERTENCIA: Secuencia '" << nombreSecuencia 
                         << "' descartada por ancho inconsistente\n";
            }

            // Si encontramos otra cabecera, retroceder
            if (!linea.empty() && linea[0] == '>') {
                archivo.seekg(archivo.tellg() - static_cast<std::streampos>(linea.length() + 1));
            }
        }
    }

    archivo.close();
    
    size_t totalCargadas = VectorSecuencias.size();
    
    if(totalCargadas == 0){
        std::cout << nombreArchivo << " no contiene ninguna secuencia.\n";
        return false;
    } else if(totalCargadas == 1){
        std::cout << "1 secuencia cargada correctamente desde " << nombreArchivo << "\n";
    } else {
        std::cout << totalCargadas << " secuencias cargadas correctamente desde " << nombreArchivo << "\n";
    }
    
    return true;
}

bool GestorDeGenomas::GuardarFASTA(std::string nombreArchivo){
    if(VectorSecuencias.empty()){
        std::cout << "ERROR: no hay secuencias cargadas en memoria\n";
        return false;
    }

    std::ofstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        std::cout << "ERROR guardando en el archivo " << nombreArchivo << "\n";
        return false;
    }

    for(size_t i = 0; i < VectorSecuencias.size(); i++){
        archivo << ">" << VectorSecuencias[i].GetNombre() << "\n";
        
        std::vector<Genomas> genomas = VectorSecuencias[i].GetGenomas();
        for(size_t j = 0; j < genomas.size(); j++){
            std::deque<char> genomaActual = genomas[j].GetGenomas();
            for(size_t k = 0; k < genomaActual.size(); k++){
                archivo << genomaActual[k];
            }
            archivo << "\n";
        }
    }

    archivo.close();
    std::cout << "Las secuencias han sido guardadas en " << nombreArchivo << "\n";
    return true;
}

// Agrega una nueva secuencia al gestor.
void GestorDeGenomas::AñadirSecuencias(Secuencia S){
    VectorSecuencias.push_back(S);
}

// Elimina todas las secuencias almacenadas en memoria.
void GestorDeGenomas::LimpiarSecuencias(){
    VectorSecuencias.clear();
}

void GestorDeGenomas::ListarSecuencias(){
    if(VectorSecuencias.empty()){ // Si no hay secuencias cargadas
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    std::cout << "Hay " << VectorSecuencias.size() <<" secuencias cargadas en memoria:\n";
    
    std::vector<Secuencia>::iterator it; // Iterador de secuencias
    
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){ // Recorre cada secuencia
        int tipos_bases = 0; // Contador de tipos de bases diferentes
        std::vector<struct histograma> histograma = it->histogramaSecuencia(); // CORRECCIÓN: usar struct histograma
        
        // Crear un mapa para facilitar el acceso a las frecuencias
        bool tiene_A = false, tiene_C = false, tiene_G = false, tiene_T = false, tiene_U = false;
        
        // Recorrer el histograma para verificar qué bases están presentes
        for(size_t i = 0; i < histograma.size(); i++){
            char base = histograma[i].Gen;
            
            if(base == 'A' && histograma[i].Repeticiones > 0) tiene_A = true;
            if(base == 'C' && histograma[i].Repeticiones > 0) tiene_C = true;
            if(base == 'G' && histograma[i].Repeticiones > 0) tiene_G = true;
            if(base == 'T' && histograma[i].Repeticiones > 0) tiene_T = true;
            if(base == 'U' && histograma[i].Repeticiones > 0) tiene_U = true;
        }
        
        // Contar tipos de bases básicas presentes
        if(tiene_A) tipos_bases++;
        if(tiene_C) tipos_bases++;
        if(tiene_G) tipos_bases++;
        if(tiene_T) tipos_bases++;
        if(tiene_U) tipos_bases++;
        
        // Verificar bases ambiguas que representen tipos faltantes
        for(size_t i = 0; i < histograma.size(); i++){
            char base = histograma[i].Gen;
            int freq = histograma[i].Repeticiones;
            
            if(freq == 0) continue;
            
            // Si falta A y hay bases ambiguas que la representen
            if(!tiene_A && (base == 'R' || base == 'M' || base == 'W' || base == 'D' || 
                           base == 'H' || base == 'V' || base == 'N')) {
                tiene_A = true;
                tipos_bases++;
            }
            
            // Si falta C y hay bases ambiguas que la representen
            if(!tiene_C && (base == 'Y' || base == 'M' || base == 'S' || base == 'B' || 
                           base == 'H' || base == 'V' || base == 'N')) {
                tiene_C = true;
                tipos_bases++;
            }
            
            // Si falta G y hay bases ambiguas que la representen
            if(!tiene_G && (base == 'R' || base == 'K' || base == 'S' || base == 'B' || 
                           base == 'D' || base == 'V' || base == 'N')) {
                tiene_G = true;
                tipos_bases++;
            }
            
            // Si falta T y hay bases ambiguas que la representen
            if(!tiene_T && (base == 'Y' || base == 'K' || base == 'W' || base == 'B' || 
                           base == 'D' || base == 'H' || base == 'N')) {
                tiene_T = true;
                tipos_bases++;
            }
            
            // Si falta U y hay bases ambiguas que la representen
            if(!tiene_U && (base == 'Y' || base == 'K' || base == 'W' || base == 'B' || 
                           base == 'D' || base == 'H' || base == 'N')) {
                tiene_U = true;
                tipos_bases++;
            }
        }
        
        std::cout << "Secuencia " << it->GetNombre() << " contiene " << tipos_bases << " tipos de bases.\n";
    }
}

// Devuelve todas las secuencias almacenadas en el gestor.
std::vector<Secuencia> GestorDeGenomas::getSecuencias(){
    return VectorSecuencias;
}

// Genera y muestra en consola el histograma de una secuencia específica.
void GestorDeGenomas::Histograma(std::string Nombre){
    if(VectorSecuencias.empty()){ // Si no hay secuencias cargadas
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int i;
    bool encontro = false;
    std::vector<Secuencia>::iterator it = VectorSecuencias.begin();

    // Busca la secuencia con el nombre dado
    for(i = 0; it != VectorSecuencias.end(); it++){
        if(Nombre == (it->GetNombre())){ // Si encuentra coincidencia
            encontro = true;
            break;
        }
        i++;
    }
    it = VectorSecuencias.begin();

    if(encontro){ // Si encontró la secuencia
        std::vector<struct histograma> Histograma = (it+i)->histogramaSecuencia(); // Obtiene histograma
        std::vector<struct histograma>::iterator aux = Histograma.begin(); // Iterador al inicio del histograma

        // Imprime los conteos de cada símbolo
        std::cout << "Histograma de " << Nombre << "\n";
        for(; aux != Histograma.end();aux++){
            std::cout<< (*(aux)).Gen << ": " << (*(aux)).Repeticiones <<"\n";
        }
    }else{
        std::cout << "ERROR: Secuencia invalida\n";
    }
}

// Cuenta la cantidad de veces que aparece una subsecuencia en todas las secuencias.
int GestorDeGenomas::Cantidad_Subsecuencias(std::string Subsecuencia){
    std::vector<Secuencia>::iterator it;
    int Contador = 0;
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){ // Recorre cada secuencia
        Contador += it->Cantidad_Subsecuencias(Subsecuencia); // Suma las ocurrencias
    }
    return Contador; // Devuelve el total
}

// Busca y enmascara todas las ocurrencias de una subsecuencia en todas las secuencias.
int GestorDeGenomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    std::vector<Secuencia>::iterator it;
    int Contador = 0;
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){ // Recorre cada secuencia
        Contador += it->Enmascarar_Subsecuencias(Subsecuencia); // Suma las ocurrencias enmascaradas
    }
    return Contador; // Devuelve el total enmascarado
}
