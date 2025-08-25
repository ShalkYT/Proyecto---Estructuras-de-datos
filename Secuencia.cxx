#include "Secuencia.h"

void Secuencia::AñadirGenomas(std::string Fila){
    Genoma G;
    G.SetFila(Fila);
    Secuencia::Genomas.push_back(G);
}

void Secuencia::SetNombre(std::string Nombre){
    this.Nombre = Nombre;
}