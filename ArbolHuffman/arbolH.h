#include "nodo.h"
#include <iostream>
#include <string>

class arbolH{
    private:
        nodo* raiz;
        void insertar(nodo* &n, struct caracter c);
        void inOrden(nodo* n);
        std::string codificar(nodo* n, char c);
        char decodificar(nodo* n, std::string codigo);

    public:
        arbolH();
        void insertar(struct caracter c);
        void inOrden();
        std::string codificar(char c);
        char decodificar(std::string codigo);

};