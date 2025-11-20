#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>

struct nodo_ {
    int fila;
    int columna;
    char valor;
};

struct ResultadoRuta {
    std::vector<int> camino;
    float costo = 0;
    char bases[2];
    int a,b, ancho;
};

struct resultadoDijkstra{
    std::vector<float> dist;
    std::vector<int> prev;
};

class grafo {
private:
    std::vector<nodo_> nodos;
    std::vector<int> longFila; 

public:
    int anchoLinea;
    grafo(int anchoLinea);

    void insertarNodo(char valor);
    int index(int fila, int columna);
    bool dentro(int fila, int columna);
    std::vector<nodo_> vecinos(int fila, int columna);
    double pesoEntre(int f1, int c1, int f2, int c2);
    resultadoDijkstra dijkstra(int f1, int c1);
    ResultadoRuta ruta_mas_corta(int f1, int c1, int f2, int c2);
    ResultadoRuta base_remota(int f1, int c1);

    void imprimir();
};

#endif
