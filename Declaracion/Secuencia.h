// ===================================================================================
// File:        Secuencia.h
// Autor:       Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:        2025-09-03
// Descripción: Declaración de la clase Secuencia, la cual almacena y administra
//              múltiples objetos de tipo Genomas. Permite asignar un nombre a la
//              secuencia, añadir genomas, contar el total de bases, verificar si los
//              genomas están completos, generar un histograma y trabajar con
//              subsecuencias (contarlas o enmascararlas).
//
//              Operaciones principales:
//              ----------------------------------------------------------------------
//              void AñadirGenomas(std::deque<char> Genomas)
//                  Agrega un nuevo objeto Genomas construido a partir de un deque.
//
//              void SetNombre(std::string Nombre)
//                  Asigna un nombre a la secuencia.
//
//              std::string GetNombre()
//                  Devuelve el nombre actual de la secuencia.
//
//              std::vector<Genomas> GetGenomas()
//                  Devuelve la lista de genomas almacenados.
//
//              long long ContarBases()
//                  Cuenta la cantidad total de bases en todos los genomas.
//
//              bool GenomasCompletos()
//                  Verifica si todos los genomas están completos.
//
//              std::vector<int> histogramaSecuencia()
//                  Genera y devuelve un histograma acumulado de bases.
//
//              int Cantidad_Subsecuencias(std::string Subsecuencia)
//                  Cuenta cuántas veces aparece una subsecuencia.
//
//              int Enmascarar_Subsecuencias(std::string Subsecuencia)
//                  Enmascara todas las ocurrencias de una subsecuencia.
// ===================================================================================

#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <vector>
#include <deque>
#include "Genomas.h"
#include "../Grafos/grafo.h"

// Clase que representa una secuencia de genomas y permite realizar
// operaciones de análisis, conteo y manipulación de subsecuencias.
class Secuencia{ 
public:
    // Agrega un genoma representado como un deque de caracteres.
    void AñadirGenomas(std::deque<char> Genomas);

    // Asigna un nombre a la secuencia.
    void SetNombre(std::string Nombre);

    // Devuelve el nombre de la secuencia.
    std::string GetNombre();

    // Devuelve el conjunto de genomas almacenados.
    std::vector<Genomas> GetGenomas();

    // Cuenta el total de bases en todos los genomas.
    int ContarBases();

    // Verifica si todos los genomas están completos.
    bool GenomasCompletos();

    // Genera y devuelve el histograma acumulado de bases de la secuencia.
    std::vector<struct histograma> histogramaSecuencia();

    // Cuenta cuántas veces aparece una subsecuencia dentro de todos los genomas.
    int Cantidad_Subsecuencias(std::string Subsecuencia);

    // Enmascara todas las ocurrencias de una subsecuencia en los genomas.
    int Enmascarar_Subsecuencias(std::string Subsecuencia);

    grafo llenar_grafo();

    // Utiliza grafos y la funcion de dikstra para hallar la ruta mas corta y su costo
    ResultadoRuta ruta_mas_corta(int i, int j, int x, int y);

    ResultadoRuta base_remota(int i, int j);

private:
    std::vector<Genomas> VectorGenomas; // Colección de genomas que forman la secuencia.
    std::string Nombre; // Nombre asignado a la secuencia.
};

#endif // SECUENCIA_H
