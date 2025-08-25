#include "GestorDeGenomas.h"

void GestorDeGenomas::AñadirSecuencias(Secuencia S){
    Secuencias.push_back(S);
}

void GestorDeGenomas::LimpiarSecuencias(){
    Secuencias.clear();
}