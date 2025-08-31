#include "Secuencia.h"
#include <iostream>

void Secuencia::AñadirGenomas(std::deque<char> Genoma){
    Genomas G;
    G.SetGenoma(Genoma);
    VectorGenomas.push_back(G);
}

void Secuencia::SetNombre(std::string Nombre){
    this->Nombre = Nombre;
}

std::string Secuencia::GetNombre(){
    return Nombre;
}

std::vector<Genomas> Secuencia::GetGenomas(){
    return VectorGenomas;
}

int Secuencia::ContarBases(){
    int Count = 0;

    std::vector<Genomas>::iterator it;
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){
        Count += it->ContarBases();
    }

    return Count;
}

bool Secuencia::GenomasCompletos(){
    bool Completos = true;

    std::vector<Genomas>::iterator it;
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){
        if(!(it->EsCompleta())){
            Completos = false;
        }
    }

    return Completos;
}

std::vector<int> Secuencia::histogramaSecuencia(){
    std::vector<int> Count(6,0);
    std::vector<int>::iterator itHistograma = Count.begin();
    std::vector<Genomas>::iterator itGenomas;
    for(itGenomas = VectorGenomas.begin(); itGenomas != VectorGenomas.end(); itGenomas++){
        std::vector<int> temp = itGenomas->ConteoHistograma();
        std::vector<int>::iterator aux = temp.begin();
        *(itHistograma) += *(aux);
        *(itHistograma + 1) += *(aux + 1);
        *(itHistograma + 2) += *(aux + 2);
        *(itHistograma + 3) += *(aux + 3);
        *(itHistograma + 4) += *(aux + 4);
        *(itHistograma + 5) += *(aux + 5);
    }
    return Count;
}

int Secuencia::Cantidad_Subsecuencias(std::string Subsecuencia){
    std::vector<Genomas>::iterator it;
    int Contador = 0;

    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){
        Contador += it->Cantidad_Subsecuencias(Subsecuencia);
    }

    return Contador;
}

int Secuencia::Enmascarar_Subsecuencias(std::string Subsecuencia){
    std::vector<Genomas>::iterator it;
    int Contador = 0;

    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){
        Contador += it->Enmascarar_Subsecuencias(Subsecuencia);
    }

    return Contador;
}