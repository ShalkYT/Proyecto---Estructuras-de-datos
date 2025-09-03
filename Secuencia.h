#ifndef SECUENCIA_H // Evita la inclusión múltiple del archivo de cabecera
#define SECUENCIA_H // Marca el inicio de la definición única

#include <vector> // Incluye la librería para usar std::vector
#include <deque> // Incluye la librería para usar std::deque
#include "Genomas.h" // Incluye la definición de la clase Genomas

class Secuencia{ // Define la clase Secuencia
public:
    void AñadirGenomas(std::deque<char> Genomas); // Añade un genoma al vector de genomas
    void SetNombre(std::string Nombre); // Asigna un nombre a la secuencia
    std::string GetNombre(); // Devuelve el nombre de la secuencia
    std::vector<Genomas> GetGenomas(); // Devuelve el vector de genomas
    long long ContarBases(); // Cuenta el total de bases en todos los genomas
    bool GenomasCompletos(); // Verifica si todos los genomas están completos
    std::vector<int> histogramaSecuencia(); // Devuelve el histograma acumulado de la secuencia
    int Cantidad_Subsecuencias(std::string Subsecuencia); // Cuenta cuántas veces aparece una subsecuencia
    int Enmascarar_Subsecuencias(std::string Subsecuencia); // Enmascara una subsecuencia en todos los genomas

private:
    std::vector<Genomas> VectorGenomas; // Contenedor de genomas asociados a la secuencia
    std::string Nombre; // Nombre de la secuencia
};
#endif // SECUENCIA_H // Marca el fin de la inclusión única
