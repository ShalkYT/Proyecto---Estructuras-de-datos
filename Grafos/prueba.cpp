#include "grafo.h"
#include <iostream>
#include <vector>

void imprimirGrafo(grafo &g, int ancho){
    int total = ancho * ancho;
    int f, c;

    std::cout << "\nGrafo (" << ancho << " x " << ancho << "):\n";

    for(int i = 0; i < total; i++){
        f = i / ancho;
        c = i % ancho;

        std::cout << ". ";
        if(c == ancho - 1) std::cout << "\n";
    }
}

int main(){
    int ancho = 5;

    grafo G(ancho);

    // Insertar 25 nodos ('A', 'B', 'C', ...)
    char val = 'A';
    for(int i = 0; i < ancho * ancho; i++){
        G.insertarNodo(val);
        if(val == 'Z') val = 'A';
        else val++;
    }

    std::cout << "Grafo creado e inicializado con "
              << ancho * ancho << " nodos.\n";

    imprimirGrafo(G, ancho);

    // Probar Dijkstra
    std::cout << "\nEjecutando Dijkstra desde (0,0) hasta (4,4)\n";

    std::vector<int> camino = G.dijkstra(0, 0, 4, 4);

    if(camino.size() == 0){
        std::cout << "No existe camino.\n";
        return 0;
    }

    std::cout << "\nCamino encontrado:\n";
    for(int i = 0; i < camino.size(); i++){
        int idx = camino[i];
        int f = idx / ancho;
        int c = idx % ancho;

        std::cout << "(" << f << "," << c << ")";
        if(i < camino.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";

    return 0;
}
