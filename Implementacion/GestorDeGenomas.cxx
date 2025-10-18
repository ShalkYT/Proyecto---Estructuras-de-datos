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
#include <iostream>

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
