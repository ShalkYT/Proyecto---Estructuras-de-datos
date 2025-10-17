#ifndef NODO_H
#define NODO_H

struct caracter{
    char Gen;
    int Repeticiones;
};

struct nodo{
    char caracter;
    nodo* izq
    nodo* der;
    int altura;

    nodo(char car);
    void actualizarAltura();
};

#endif // NODO_H