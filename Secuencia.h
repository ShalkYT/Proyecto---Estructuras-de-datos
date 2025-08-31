#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include <deque>
#include "Genomas.h"

class Secuencia{ 
public:
    void AñadirGenomas(std::deque<char> Genomas);
    void SetNombre(std::string Nombre);
    std::string GetNombre();
    std::vector<Genomas> GetGenomas();
    int ContarBases();
    bool GenomasCompletos();
    std::vector<int> histogramaSecuencia();
    int Cantidad_Subsecuencias(std::string Subsecuencia);
    int Enmascarar_Subsecuencias(std::string Subsecuencia);

private:
    std::vector<Genomas> VectorGenomas;
    std::string Nombre;
};
#endif // SECUENCIA_H