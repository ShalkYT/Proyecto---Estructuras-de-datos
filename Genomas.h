#ifndef GENOMAS_H
#define GENOMAS_H

#include <string>
#include <vector>
#include <algorithm>
#include <deque>

class Genomas{
public:
    void SetGenoma(std::deque<char> Genomas);
    std::deque<char> GetGenomas();
    int ContarBases();
    bool EsCompleta();
    std::vector<int> ConteoHistograma();
    int Cantidad_Subsecuencias(std::string Subsecuencia);
    int Enmascarar_Subsecuencias(std::string Subsecuencia);
private:
    std::deque<char> Genomas;
};

#endif // GENOMAS_H