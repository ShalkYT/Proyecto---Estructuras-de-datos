#ifndef GESTOR_DE_GENOMAS_H
#define GESTOR_DE_GENOMAS_H

#include <vector>
#include "Secuencia.h"

class GestorDeGenomas{
public:
    void AñadirSecuencias(Secuencia S);
    void LimpiarSecuencias();
private:
    std::vector<Secuencia> VectorSecuencias;  

};

#endif // GESTOR_DE_GENOMAS_H