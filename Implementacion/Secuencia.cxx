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
std::vector<struct histograma> Secuencia::histogramaSecuencia(){
    std::vector<struct histograma> histograma;
    bool encontro;
    struct histograma temp_his;

    std::vector<struct histograma>::iterator his;
    std::vector<Genomas>::iterator itGenomas; // Iterador para recorrer los genomas

    for(itGenomas = VectorGenomas.begin(); itGenomas != VectorGenomas.end(); itGenomas++){ // Recorre todos los genomas
        std::vector<struct histograma> temp = itGenomas->ConteoHistograma(); // Obtiene el histograma del genoma actual
        std::vector<struct histograma>::iterator aux = temp.begin(); // Iterador al inicio del histograma temporal

        for(; aux != temp.end(); aux++){
            encontro = false;
            for(his = histograma.begin(); his != histograma.end();his++){
                if((*(aux)).Gen == (*(his)).Gen){
                    (*(his)).Repeticiones += (*(aux)).Repeticiones;
                    encontro = true;
                    break;
                }
            }
            if(!encontro){
                temp_his.Gen = (*(aux)).Gen;
                temp_his.Repeticiones = (*(aux)).Repeticiones;
                histograma.push_back(temp_his);
            }
        }
        
    }
    return histograma; // Devuelve el histograma acumulado
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

grafo Secuencia::llenar_grafo(){
    int anchoDeLinea = VectorGenomas[0].ContarBases();
    grafo graf(anchoDeLinea);

    std::vector<Genomas>::iterator vec = VectorGenomas.begin();
    std::deque<char>::iterator deq;
    
    for(;vec != VectorGenomas.end();vec++){
        std::deque<char> temp = vec->GetGenomas();
        for(deq = temp.begin(); deq != temp.end(); deq++){
            graf.insertarNodo(*deq);
        }
    }

    return graf;
}

ResultadoRuta Secuencia::ruta_mas_corta(int i, int j, int x, int y){
    // Crea un grafo tipo cuadricula que tiene en cuenta un ancho de linea del primer gen
    
    grafo graf = llenar_grafo();

    ResultadoRuta resultado = graf.ruta_mas_corta(i,j,x,y);
    return resultado;
}

ResultadoRuta Secuencia::base_remota(int i, int j){

    grafo graf = llenar_grafo();

    ResultadoRuta resultado = graf.base_remota(i,j);
    return resultado;

}