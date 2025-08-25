#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include "Genomas.h"

class Secuencia{ 
public:
    void AñadirGenomas(Genomas G);

private:
    std::vector<Genomas> Genomas;
}
#endif // SECUENCIA_H