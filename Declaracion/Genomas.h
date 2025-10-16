// ===================================================================================
// File:        Genomas.h
// Autor:       Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:        2025-09-03
// Descripción: Declaración de la clase Genomas, la cual representa un genoma
//              almacenado como una secuencia de caracteres en un deque. 
//              Permite realizar operaciones de conteo, validación de completitud,
//              generación de histogramas, búsqueda de subsecuencias y enmascaramiento.
//
//              Operaciones principales:
//              ----------------------------------------------------------------------
//              void SetGenoma(std::deque<char> Genomas)
//                  Asigna una secuencia de caracteres al objeto Genomas.
//
//              std::deque<char> GetGenomas()
//                  Devuelve la secuencia completa del genoma.
//
//              long long ContarBases()
//                  Cuenta el número total de bases en el genoma.
//
//              bool EsCompleta()
//                  Verifica si el genoma cumple con la condición de estar completo.
//
//              std::vector<int> ConteoHistograma()
//                  Genera un histograma con las frecuencias de las bases.
//
//              int Cantidad_Subsecuencias(std::string Subsecuencia)
//                  Cuenta cuántas veces aparece una subsecuencia en el genoma.
//
//              int Enmascarar_Subsecuencias(std::string Subsecuencia)
//                  Enmascara todas las ocurrencias de una subsecuencia en el genoma.
// ===================================================================================

#ifndef GENOMAS_H
#define GENOMAS_H

#include <string>
#include <vector>
#include <algorithm>
#include <deque>

struct histograma{
    char Gen;
    int Repeticiones;
};

// Clase que representa un genoma como una secuencia de caracteres
// y permite realizar operaciones de análisis y manipulación.
class Genomas {
public:
    // Asigna un genoma al objeto a partir de una secuencia de caracteres.
    void SetGenoma(std::deque<char> Genomas);

    // Devuelve la secuencia completa del genoma.
    std::deque<char> GetGenomas();

    // Cuenta la cantidad total de bases en el genoma.
    long long ContarBases();

    // Verifica si el genoma cumple con la condición de estar completo.
    bool EsCompleta();

    // Genera un histograma con las frecuencias de las bases del genoma.
    std::vector<struct histograma> ConteoHistograma();

    // Cuenta cuántas veces aparece una subsecuencia dentro del genoma.
    int Cantidad_Subsecuencias(std::string Subsecuencia);

    // Enmascara todas las apariciones de una subsecuencia en el genoma.
    int Enmascarar_Subsecuencias(std::string Subsecuencia);

private:
    // Verifica si un carácter del genoma coincide con el carácter de búsqueda.
    bool coincide_con_patron(char codigo_busqueda, char caracter_genoma);

    // Método de depuración para comprobar la coincidencia de patrones.
    void Debug_coincide_con_patron();

    std::deque<char> Genomas; // Contenedor donde se almacena la secuencia genética.
};

#endif // GENOMAS_H
