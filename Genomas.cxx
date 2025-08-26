#include "Genomas.h"

void Genomas::SetFila(std::string Fila){
    this->Fila = Fila;
}

std::string Genomas::GetFila(){
    return Fila;
}

int Genomas::ContarBases(){
    int count = 0;
    for(long unsigned int i = 0; i < Fila.size() ; i++){
        if(Fila[i] == 'A' || Fila[i] == 'C' || Fila[i] == 'G' || Fila[i] == 'T'){
            count++;
        }
    } 
    return count;
}

bool Genomas::EsCompleta(){
    bool Completa = true;
    for(long unsigned int i = 0; i < Fila.size() ; i++){
        if(Fila[i] != 'A' && Fila[i] != 'C' && Fila[i] != 'G' && Fila[i] != 'T'){
            Completa = false;
        }
    } 
    return Completa;
}
