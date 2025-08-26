#include "Secuencia.h"
#include <iostream>

void Secuencia::AñadirGenomas(std::string Fila){
    Genomas G;
    G.SetFila(Fila);
    VectorGenomas.push_back(G);
}

void Secuencia::SetNombre(std::string Nombre){
    this->Nombre = Nombre;
}

std::string Secuencia::GetNombre(){
    return Nombre;
}

void Secuencia::ListarGenomas(){
    std::vector<Genomas>::iterator it;
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){
        std::cout << it->GetFila() << "\n";
    }
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