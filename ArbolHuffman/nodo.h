#ifndef NODO_H
#define NODO_H

#include <algorithm>

struct caracter{
    char Gen;
    int Repeticiones;
};

struct nodo{
    struct caracter caracter;
    nodo* izq;
    nodo* der;
    int altura;

    nodo(struct caracter car);
    void actualizarAltura();
};

#endif // NODO_H