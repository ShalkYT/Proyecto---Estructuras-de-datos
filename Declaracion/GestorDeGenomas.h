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

#ifndef GESTORDEGENOMAS_H
#define GESTORDEGENOMAS_H

#include "Secuencia.h"
#include <vector>
#include <string>

class GestorDeGenomas {
private:
    std::vector<Secuencia> VectorSecuencias;

public:
    // ========== OPERACIONES CON ARCHIVOS ==========
    
    // Carga secuencias desde un archivo FASTA
    bool CargarFASTA(std::string nombreArchivo);
    
    // Guarda las secuencias en memoria a un archivo FASTA
    bool GuardarFASTA(std::string nombreArchivo);
    
    // Codifica las secuencias en memoria usando Huffman
    void CodificarHuffman(std::string nombreArchivo);
    
    // Decodifica un archivo Huffman y carga las secuencias en memoria

    
    
    // ========== GESTIÓN DE SECUENCIAS ==========
    
    // Añade una secuencia a la memoria
    void AñadirSecuencias(Secuencia S);
    
    // Elimina todas las secuencias de la memoria
    void LimpiarSecuencias();
    
    // Retorna el vector de secuencias
    std::vector<Secuencia> getSecuencias();
    
    
    // ========== CONSULTAS Y ANÁLISIS ==========
    
    // Lista las secuencias cargadas con información básica
    void ListarSecuencias();
    
    // Muestra el histograma de una secuencia específica
    void Histograma(std::string Nombre);
    
    // Cuenta cuántas veces aparece una subsecuencia
    int Cantidad_Subsecuencias(std::string Subsecuencia);
    
    // Enmascara (reemplaza con 'X') todas las ocurrencias de una subsecuencia
    int Enmascarar_Subsecuencias(std::string Subsecuencia);
};

#endif // GESTORDEGENOMAS_H