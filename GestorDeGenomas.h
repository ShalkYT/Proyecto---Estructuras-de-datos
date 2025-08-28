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
    void Histograma(std::string Nombre);
    int Cantidad_Subsecuencias(std::string Subsecuencia);
    int Enmascarar_Subsecuencias(std::string Subsecuencia);
private:
    std::vector<Secuencia> VectorSecuencias;  
    
};

#endif // GESTOR_DE_GENOMAS_H