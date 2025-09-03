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

void GestorDeGenomas::Histograma(std::string Nombre){
    if(VectorSecuencias.empty()){
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int i;
    bool encontro = false;
    std::vector<Secuencia>::iterator it = VectorSecuencias.begin();
    for(i = 0; it != VectorSecuencias.end(); it++){
        if(Nombre == (it->GetNombre())){
            encontro = true;
            break;
        }
        i++;
    }
    it = VectorSecuencias.begin();

    if(encontro){
        std::vector<int> Histograma = (it+i)->histogramaSecuencia();
        std::vector<int>::iterator aux = Histograma.begin();
        std::cout << "Histograma de " << Nombre;
        std::cout << "\nA : " << *(aux) << "\nC : " << *(aux+1) << "\nG : " << *(aux+2) << "\nT : " << *(aux+3) << "\nU : " << *(aux+4) << "\n- : " << *(aux+5) << "\n"; 

    }else{
        std::cout << "ERROR: Secuencia invalida\n";
    }
}

int GestorDeGenomas::Cantidad_Subsecuencias(std::string Subsecuencia){
    std::vector<Secuencia>::iterator it;
    int Contador = 0;
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){
        Contador += it->Cantidad_Subsecuencias(Subsecuencia);
    }
    return Contador;
}

int GestorDeGenomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    std::vector<Secuencia>::iterator it;
    int Contador = 0;
    for(it = VectorSecuencias.begin(); it != VectorSecuencias.end(); it++){
        Contador += it->Enmascarar_Subsecuencias(Subsecuencia);
    }
    return Contador;
}