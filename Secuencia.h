#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include "Genomas.h"

class Secuencia{ 
public:
    void AñadirGenomas(std::string Fila);
    void SetNombre(std::string Nombre);
    std::string GetNombre();
    void ListarGenomas();
    int ContarBases();
    bool GenomasCompletos();

private:
    std::vector<Genomas> VectorGenomas;
    std::string Nombre;

};
#endif // SECUENCIA_H