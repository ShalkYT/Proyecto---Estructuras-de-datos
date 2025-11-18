#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <vector>

struct nodo{
    char valor;
    int fila, columna;
};

class grafo{

    private:

    std::vector<struct nodo> nodos;
    int anchoLinea;

    int index(int fila, int columna);
    bool dentro(int fila, int columna);
    std::vector<struct nodo> vecinos(int fila, int columna);
    double pesoEntre(int f1, int c1, int f2, int c2);
    double pesoVecino(int fila, int columna, char dir);
    
    
    public:

    grafo(int anchoLinea);
    void insertarNodo(char valor);
    std::vector<int> dijkstra(int f1, int c1, int f2, int c2);

};

#endif