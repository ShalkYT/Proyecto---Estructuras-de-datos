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
        std::vector<int> histograma = it->histogramaSecuencia(); // Obtiene el histograma
        
        // Cuenta los tipos de bases básicas presentes (A, C, G, T, U)
        if(histograma[0] > 0) tipos_bases++; // A
        if(histograma[1] > 0) tipos_bases++; // C
        if(histograma[2] > 0) tipos_bases++; // G
        if(histograma[3] > 0) tipos_bases++; // T
        if(histograma[4] > 0) tipos_bases++; // U
        
        // Verificar bases ambiguas que representen tipos faltantes
        bool tiene_A = (histograma[0] > 0);
        bool tiene_C = (histograma[1] > 0);
        bool tiene_G = (histograma[2] > 0);
        bool tiene_T = (histograma[3] > 0);
        bool tiene_U = (histograma[4] > 0);
        
        // Si faltan bases básicas, verificar si están representadas por ambiguas
        if(!tiene_A && (histograma[5] > 0 || histograma[9] > 0 || histograma[11] > 0 || 
                        histograma[13] > 0 || histograma[14] > 0 || histograma[15] > 0 || histograma[16] > 0)) {
            tipos_bases++; // A representada por ambiguas
        }
        if(!tiene_C && (histograma[7] > 0 || histograma[9] > 0 || histograma[10] > 0 || 
                        histograma[12] > 0 || histograma[14] > 0 || histograma[15] > 0 || histograma[16] > 0)) {
            tipos_bases++; // C representada por ambiguas
        }
        if(!tiene_G && (histograma[5] > 0 || histograma[8] > 0 || histograma[10] > 0 || 
                        histograma[12] > 0 || histograma[13] > 0 || histograma[15] > 0 || histograma[16] > 0)) {
            tipos_bases++; // G representada por ambiguas
        }
        if(!tiene_T && (histograma[7] > 0 || histograma[8] > 0 || histograma[11] > 0 || 
                        histograma[12] > 0 || histograma[13] > 0 || histograma[14] > 0 || histograma[16] > 0)) {
            tipos_bases++; // T representada por ambiguas
        }
        if(!tiene_U && (histograma[7] > 0 || histograma[8] > 0 || histograma[11] > 0 || 
                        histograma[12] > 0 || histograma[13] > 0 || histograma[14] > 0 || histograma[16] > 0)) {
            tipos_bases++; // U representada por ambiguas
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
        std::vector<int> Histograma = (it+i)->histogramaSecuencia(); // Obtiene histograma
        std::vector<int>::iterator aux = Histograma.begin(); // Iterador al inicio del histograma

        // Imprime los conteos de cada símbolo
        std::cout << "Histograma de " << Nombre;
        std::cout << "\nA : " << *(aux) 
                  << "\nC : " << *(aux+1) 
                  << "\nG : " << *(aux+2) 
                  << "\nT : " << *(aux+3) 
                  << "\nU : " << *(aux+4)
                  << "\nR : " << *(aux+5)
                  << "\n- : " << *(aux+6)
                  << "\nY : " << *(aux+7)
                  << "\nK : " << *(aux+8)
                  << "\nM : " << *(aux+9)
                  << "\nS : " << *(aux+10)
                  << "\nW : " << *(aux+11)
                  << "\nB : " << *(aux+12)
                  << "\nD : " << *(aux+13)
                  << "\nH : " << *(aux+14)
                  << "\nV : " << *(aux+15)
                  << "\nN : " << *(aux+16)
                  << "\nX : " << *(aux+17) << "\n"; 
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
