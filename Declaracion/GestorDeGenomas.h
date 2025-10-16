// ===================================================================================
// File:        GestorDeGenomas.h
// Autor:       Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:        2025-09-03
// Descripción: Declaración de la clase GestorDeGenomas, la cual administra múltiples
//              objetos de tipo Secuencia. Permite añadir, limpiar, listar, generar
//              histogramas y realizar operaciones sobre subsecuencias a nivel global.
//
//              Operaciones principales:
//              ----------------------------------------------------------------------
//              void AñadirSecuencias(Secuencia S)
//                  Agrega una nueva secuencia al gestor.
//
//              void LimpiarSecuencias()
//                  Elimina todas las secuencias almacenadas.
//
//              std::vector<Secuencia> getSecuencias()
//                  Devuelve el conjunto de secuencias almacenadas.
//
//              void ListarSecuencias()
//                  Muestra en consola información sobre todas las secuencias.
//
//              void Histograma(std::string Nombre)
//                  Genera y muestra en consola el histograma de una secuencia específica.
//
//              int Cantidad_Subsecuencias(std::string Subsecuencia)
//                  Cuenta cuántas veces aparece una subsecuencia en todas las secuencias.
//
//              int Enmascarar_Subsecuencias(std::string Subsecuencia)
//                  Enmascara todas las ocurrencias de una subsecuencia en todas las secuencias.
// ===================================================================================

#ifndef GESTOR_DE_GENOMAS_H
#define GESTOR_DE_GENOMAS_H

#include <vector>
#include "Secuencia.h"

// Clase que gestiona múltiples secuencias de genomas y permite realizar
// operaciones de análisis global sobre ellas.
class GestorDeGenomas{
public:
    // Agrega una nueva secuencia al gestor.
    void AñadirSecuencias(Secuencia S);

    // Elimina todas las secuencias almacenadas en memoria.
    void LimpiarSecuencias();

    // Devuelve el conjunto de secuencias almacenadas.
    std::vector<Secuencia> getSecuencias();

    // Lista todas las secuencias mostrando su estado en consola.
    void ListarSecuencias();

    // Genera y muestra el histograma de una secuencia específica.
    void Histograma(std::string Nombre);

    // Cuenta cuántas veces aparece una subsecuencia en todas las secuencias.
    int Cantidad_Subsecuencias(std::string Subsecuencia);

    // Enmascara todas las ocurrencias de una subsecuencia en todas las secuencias.
    int Enmascarar_Subsecuencias(std::string Subsecuencia);

private:
    std::vector<Secuencia> VectorSecuencias;  // Conjunto de secuencias almacenadas en el gestor.
};

#endif // GESTOR_DE_GENOMAS_H
