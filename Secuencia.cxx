// ===================================================================================
// File:                   Secuencia.cpp
// Autor:                  Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:       2025-09-03
// Descripción:            Implementación de los métodos de la clase Secuencia.
// ===================================================================================

#include "Secuencia.h"
#include <iostream>

// Agrega un genoma (deque de chars) como un objeto Genomas al contenedor interno.
void Secuencia::AñadirGenomas(std::deque<char> Genoma){
    Genomas G;
    G.SetGenoma(Genoma);
    VectorGenomas.push_back(G);
}

// Asigna el nombre de la secuencia.
void Secuencia::SetNombre(std::string Nombre){
    this->Nombre = Nombre;
}

// Devuelve el nombre de la secuencia.
std::string Secuencia::GetNombre(){
    return Nombre;
}

// Devuelve el vector completo de genomas almacenados.
std::vector<Genomas> Secuencia::GetGenomas(){
    return VectorGenomas;
}

// Cuenta el total de bases sumando las de todos los genomas.
int Secuencia::ContarBases(){
    int Count = 0; // Inicializa contador de bases
    std::vector<Genomas>::iterator it; // Crea iterador para recorrer los genomas
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre desde el primer hasta el último genoma
        Count += it->ContarBases(); // Suma al contador las bases del genoma actual
    }
    return Count; // Devuelve la cantidad total de bases
}

// Verifica si todos los genomas de la secuencia están completos.
bool Secuencia::GenomasCompletos(){
    bool Completos = true; // Supone que están completos
    std::vector<Genomas>::iterator it; // Iterador para recorrer genomas
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre todos los genomas
        if(!(it->EsCompleta())){ // Si algún genoma no está completo
            Completos = false; // Marca la variable como falso
        }
    }
    return Completos; // Devuelve si todos están completos o no
}

// Genera un histograma acumulado de las bases de todos los genomas.
std::vector<int> Secuencia::histogramaSecuencia(){
    std::vector<int> Count(18,0); // Vector de 18 posiciones inicializadas en cero
    std::vector<int>::iterator itHistograma = Count.begin(); // Iterador que apunta al inicio del histograma acumulado
    std::vector<Genomas>::iterator itGenomas; // Iterador para recorrer los genomas
    for(itGenomas = VectorGenomas.begin(); itGenomas != VectorGenomas.end(); itGenomas++){ // Recorre todos los genomas
        std::vector<int> temp = itGenomas->ConteoHistograma(); // Obtiene el histograma del genoma actual
        std::vector<int>::iterator aux = temp.begin(); // Iterador al inicio del histograma temporal
        *(itHistograma)     += *(aux);     // Suma posición 0
        *(itHistograma+1)   += *(aux+1);   // Suma posición 1
        *(itHistograma+2)   += *(aux+2);   // Suma posición 2
        *(itHistograma+3)   += *(aux+3);   // Suma posición 3
        *(itHistograma+4)   += *(aux+4);   // Suma posición 4
        *(itHistograma+5)   += *(aux+5);   // Suma posición 5
        *(itHistograma+6)   += *(aux+6);   // Suma posición 6
        *(itHistograma+7)   += *(aux+7);   // Suma posición 7
        *(itHistograma+8)   += *(aux+8);   // Suma posición 8
        *(itHistograma+9)   += *(aux+9);   // Suma posición 9
        *(itHistograma+10)  += *(aux+10);  // Suma posición 10
        *(itHistograma+11)  += *(aux+11);  // Suma posición 11
        *(itHistograma+12)  += *(aux+12);  // Suma posición 12
        *(itHistograma+13)  += *(aux+13);  // Suma posición 13
        *(itHistograma+14)  += *(aux+14);  // Suma posición 14
        *(itHistograma+15)  += *(aux+15);  // Suma posición 15
        *(itHistograma+16)  += *(aux+16);  // Suma posición 16
        *(itHistograma+17)  += *(aux+17);  // Suma posición 17
    }
    return Count; // Devuelve el histograma acumulado
}

// Cuenta las apariciones de una subsecuencia en todos los genomas.
int Secuencia::Cantidad_Subsecuencias(std::string Subsecuencia){
    std::vector<Genomas>::iterator it; // Iterador para recorrer genomas
    int Contador = 0; // Inicializa contador en cero
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma
        Contador += it->Cantidad_Subsecuencias(Subsecuencia); // Suma las apariciones en el genoma actual
    }
    return Contador; // Devuelve la cantidad total de apariciones
}

// Enmascara una subsecuencia en todos los genomas y cuenta cuántas fueron enmascaradas.
int Secuencia::Enmascarar_Subsecuencias(std::string Subsecuencia){
    std::vector<Genomas>::iterator it; // Iterador para recorrer genomas
    int Contador = 0; // Inicializa contador en cero
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma
        Contador += it->Enmascarar_Subsecuencias(Subsecuencia); // Suma la cantidad enmascarada en el genoma actual
    }
    return Contador; // Devuelve el total de subsecuencias enmascaradas
}
