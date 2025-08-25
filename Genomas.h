#ifndef GENOMAS_H
#define GENOMAS_H

#include <vector>
#include <string>

class Genomas{
public:

    void AgregarFila(std::string NuevaFila);
    void SetTamañoMax(int NewTamaño);

private:
    std::vector<std::string> Filas;
    int TamañoMax;
};


#endif // GENOMAS_H