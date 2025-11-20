#include "grafo.h"
#include <iostream>
#include <cmath>
#include <limits>

grafo::grafo(int anchoLinea) {
    this->anchoLinea = anchoLinea;
}

void grafo::insertarNodo(char valor){
    nodo_ Gen;
    int idx = nodos.size();

    Gen.fila    = idx / anchoLinea;
    Gen.columna = idx % anchoLinea;
    Gen.valor   = valor;

    if (Gen.columna == 0)
        longFila.push_back(0);

    longFila.back()++;

    nodos.push_back(Gen);
}

int grafo::index(int fila, int columna){
    int id = 0;
    for(int f = 0; f < fila; f++)
        id += longFila[f];

    return id + columna;
}

bool grafo::dentro(int fila, int columna){
    if (fila < 0 || fila >= (int)longFila.size())
        return false;
    if (columna < 0 || columna >= longFila[fila])
        return false;
    return true;
}

std::vector<nodo_> grafo::vecinos(int fila, int columna){
    std::vector<nodo_> vec;

    if(dentro(fila + 1, columna))
        vec.push_back(nodos[index(fila + 1, columna)]);

    if(dentro(fila - 1, columna))
        vec.push_back(nodos[index(fila - 1, columna)]);

    if(dentro(fila, columna + 1))
        vec.push_back(nodos[index(fila, columna + 1)]);

    if(dentro(fila, columna - 1))
        vec.push_back(nodos[index(fila, columna - 1)]);

    return vec;
}

double grafo::pesoEntre(int f1, int c1, int f2, int c2){
    if (!dentro(f1, c1) || !dentro(f2, c2))
        return -1;

    int id1 = index(f1, c1);
    int id2 = index(f2, c2);

    char a = nodos[id1].valor;
    char b = nodos[id2].valor;

    double diff = std::abs(int(a) - int(b));
    return 1.0 / (1.0 + diff);
}

ResultadoRuta grafo::dijkstra(int f1, int c1, int f2, int c2){
    ResultadoRuta resultado;

    if (!dentro(f1, c1)){
        resultado.bases[0] = '1';
        return resultado;
    }
    if (!dentro(f2, c2)){
        resultado.bases[1] = '1';
        return resultado;
    }

    int n = nodos.size();
    int start = index(f1, c1);
    int goal  = index(f2, c2);
    resultado.bases[0] = (nodos[start]).valor;
    resultado.bases[1] = (nodos[goal]).valor;

    std::vector<float> dist(n, std::numeric_limits<float>::infinity());
    std::vector<int> prev(n, -1);
    std::vector<bool> inQ(n, true);

    dist[start] = 0;

    while(true){
        int u = -1;
        float minDist = std::numeric_limits<float>::infinity();

        for(int i = 0; i < n; i++){
            if(inQ[i] && dist[i] < minDist){
                u = i;
                minDist = dist[i];
            }
        }

        if(u == -1) break;
        if(u == goal){
            inQ[u] = false;
            break;
        }

        inQ[u] = false;

        int uf = nodos[u].fila;
        int uc = nodos[u].columna;

        for(auto &vn : vecinos(uf, uc)){
            int v = index(vn.fila, vn.columna);

            if(!inQ[v]) continue;

            double w = pesoEntre(uf, uc, vn.fila, vn.columna);

            if(w < 0) continue;

            float alt = dist[u] + w;

            if(alt < dist[v]){
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }

    if(dist[goal] == std::numeric_limits<float>::infinity())
        return resultado;

    resultado.costo = dist[goal];

    std::vector<int> camino;
    int actual = goal;

    while(actual != -1){
        camino.push_back(actual);
        actual = prev[actual];
    }

    // invertir
    for(int i = 0; i < (int)camino.size()/2; i++){
        int tmp = camino[i];
        camino[i] = camino[camino.size()-1-i];
        camino[camino.size()-1-i] = tmp;
    }

    resultado.camino = camino;
    return resultado;
}

void grafo::imprimir() {
    for(int f = 0; f < (int)longFila.size(); f++){
        for(int c = 0; c < longFila[f]; c++){
            std::cout << nodos[index(f, c)].valor << " ";
        }
        std::cout << "\n";
    }
}
