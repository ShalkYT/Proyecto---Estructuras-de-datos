#include "GestorDeGenomas.h"
#include <iostream>

void GestorDeGenomas::AñadirSecuencias(Secuencia S){
    VectorSecuencias.push_back(S);
}

void GestorDeGenomas::LimpiarSecuencias(){
    VectorSecuencias.clear();
}

void GestorDeGenomas::ListarSecuencias(){
    if(VectorSecuencias.empty()){
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }
    std::cout << "Hay " << VectorSecuencias.size() <<" secuencias cargadas en memoria:\n";
    
    std::vector<Secuencia>::iterator it;
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){
        if(it->GenomasCompletos()){
            std::cout << "Secuencia " << it->GetNombre() << " contiene " << it->ContarBases() << " bases.\n";
        }else{
            std::cout << "Secuencia " << it->GetNombre() << " contiene al menos " << it->ContarBases() << " bases.\n";
        }
    }
}

std::vector<Secuencia> GestorDeGenomas::getSecuencias(){
    return VectorSecuencias;
}