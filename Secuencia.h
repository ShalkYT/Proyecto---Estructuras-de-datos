#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include "Genomas.h"

class Secuencia{ 
public:
    void AñadirGenomas(Genomas G);
    void SetNombre(std::string Nombre);

private:
    std::vector<Genomas> VectorGenomas;
    std::string Nombre;

};
#endif // SECUENCIA_H