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
        if(Fila[i] == 'A' || Fila[i] == 'C' || Fila[i] == 'G' || Fila[i] == 'T' || Fila[i] == 'U' || Fila[i] == '-'){
            count++;
        }
    } 
    return count;
}

bool Genomas::EsCompleta(){
    bool Completa = true;
    for(long unsigned int i = 0; i < Fila.size() ; i++){
        if(Fila[i] != 'A' && Fila[i] != 'C' && Fila[i] != 'G' && Fila[i] != 'T' && Fila[i] == 'U'){
            Completa = false;
        }
    } 
    return Completa;
}

std::vector<int> Genomas::ConteoHistograma(){
    std::vector<int> Count(6,0);
    std::vector<int>::iterator it = Count.begin();
    for(long unsigned int i = 0; i < Fila.size() ; i++){
        if(Fila[i] == 'A') (*(it))++;
        if(Fila[i] == 'C') (*(it + 1))++;
        if(Fila[i] == 'G') (*(it + 2))++;
        if(Fila[i] == 'T') (*(it + 3))++;
        if(Fila[i] == 'U') (*(it + 4))++;
        if(Fila[i] == '-') (*(it + 5))++;
    } 
    return Count;
}

int Genomas::Cantidad_Subsecuencias(std::string subsecuencia){
    int Count = 0;
    
    for(size_t pos = Fila.find(subsecuencia) ; pos != std::string::npos ; pos = Fila.find(subsecuencia, pos + 1 ))
        Count++;

    return Count;
}

int Genomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    int Count = 0;

    for(size_t pos = Fila.find(Subsecuencia) ; pos != std::string::npos ; pos = Fila.find(Subsecuencia, pos + 1 )){
        Count++;
        Fila.replace(pos,Subsecuencia.size(),std::string(Subsecuencia.length(), 'X'));
    }
    return Count;
}