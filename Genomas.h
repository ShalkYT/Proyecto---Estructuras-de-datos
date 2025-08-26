#ifndef GENOMAS_H
#define GENOMAS_H

#include <string>

class Genomas{
public:
    void SetFila(std::string Fila);
    std::string GetFila();
    int ContarBases();
    bool EsCompleta();
private:
    std::string Fila;
};


#endif // GENOMAS_H