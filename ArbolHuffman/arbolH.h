#ifndef ARBOLH_H
#define ARBOLH_H

#include "nodo.h"
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

class arbolH{
    private:
        nodo* raiz;
        
        // Comparador para la cola de prioridad (min-heap)
        // Retorna true si 'a' tiene MAYOR frecuencia que 'b'
        // Esto hace que los nodos con MENOR frecuencia tengan mayor prioridad
        struct CompararNodos {
            bool operator()(nodo* a, nodo* b) {
                return a->caracter.Repeticiones > b->caracter.Repeticiones;
            }
        };
        
        // Genera códigos Huffman recursivamente
        void generarCodigos(nodo* n, std::string codigo, std::map<char, std::string>& tabla);
        
        // Destruye el árbol recursivamente (para el destructor)
        void destruirArbol(nodo* n);
        
    public:
        // Constructor y destructor
        arbolH();
        ~arbolH();
        
        // Construye el árbol de Huffman a partir de un histograma
        // histograma: vector con pares (carácter, frecuencia)
        void construirArbol(std::vector<struct caracter> histograma);
        
        // Genera la tabla de códigos Huffman (mapa: carácter -> código binario)
        std::map<char, std::string> generarTablaCodigos();
        
        // Codifica una secuencia completa usando los códigos Huffman
        // Retorna: string de '0' y '1'
        std::string codificarSecuencia(const std::string& secuencia);
        
        // Decodifica una secuencia binaria usando el árbol de Huffman
        // codigoBinario: string de '0' y '1'
        // Retorna: secuencia original
        std::string decodificarSecuencia(const std::string& codigoBinario);
        
        // Obtiene el histograma recorriendo el árbol
        // Útil para verificación y debugging
        std::vector<struct caracter> obtenerHistograma();
        
        // Getter para la raíz (si se necesita acceso directo)
        nodo* getRaiz() { return raiz; }
};

#endif // ARBOLH_H