#ifndef GENOMAS_H
#define GENOMAS_H

#include <string>
#include <vector>
#include <algorithm>

class Genomas{
public:
    void SetFila(std::string Fila);
    std::string GetFila();
    int ContarBases();
    bool EsCompleta();
    std::vector<int> ConteoHistograma();
    int Cantidad_Subsecuencias(std::string subsecuencia);
private:
    std::string Fila;
};


#endif // GENOMAS_H