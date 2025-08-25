#include "Genomas.h"

void Genomas::AgregarFila(std::string NuevaFila){
    Filas.push_back(NuevaFila);
}

void Genomas::SetTamañoMax(int NewTamaño){
    Genomas::TamañoMax = NewTamaño;
}
