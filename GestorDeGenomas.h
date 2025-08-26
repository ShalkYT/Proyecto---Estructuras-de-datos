#ifndef GESTOR_DE_GENOMAS_H
#define GESTOR_DE_GENOMAS_H

#include <vector>
#include "Secuencia.h"

class GestorDeGenomas{
public:
    void AñadirSecuencias(Secuencia S);
    void LimpiarSecuencias();
    std::vector<Secuencia> getSecuencias();
    void ListarSecuencias();
private:
    std::vector<Secuencia> VectorSecuencias;  

};

#endif // GESTOR_DE_GENOMAS_H