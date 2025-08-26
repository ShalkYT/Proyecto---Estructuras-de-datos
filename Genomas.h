#ifndef GENOMAS_H
#define GENOMAS_H

#include <string>
#include <vector>

class Genomas{
public:
    void SetFila(std::string Fila);
    std::string GetFila();
    int ContarBases();
    bool EsCompleta();
    std::vector<int> ConteoHistograma();
private:
    std::string Fila;
};


#endif // GENOMAS_H