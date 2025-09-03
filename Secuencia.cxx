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

long long Secuencia::ContarBases(){
    long long Count = 0;

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
    std::vector<int> Count(18,0);
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
        *(itHistograma + 6) += *(aux + 6);
        *(itHistograma + 7) += *(aux + 7);
        *(itHistograma + 8) += *(aux + 8);
        *(itHistograma + 9) += *(aux + 9);
        *(itHistograma + 10) += *(aux + 10);
        *(itHistograma + 11) += *(aux + 11);
        *(itHistograma + 12) += *(aux + 12);
        *(itHistograma + 13) += *(aux + 13);
        *(itHistograma + 14) += *(aux + 14);
        *(itHistograma + 15) += *(aux + 15);
        *(itHistograma + 16) += *(aux + 16);
        *(itHistograma + 17) += *(aux + 17);
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