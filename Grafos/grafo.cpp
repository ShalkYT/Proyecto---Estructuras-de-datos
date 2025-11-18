#include "grafo.h"
#include <cmath>
#include <iostream>
#include <limits>

grafo::grafo(int anchoLinea){
    this->anchoLinea = anchoLinea;
}

int grafo::index(int fila, int columna){
    return fila * anchoLinea + columna;
}

void grafo::insertarNodo(char valor){
    nodo Gen;
    int index = nodos.size(); 

    Gen.fila    = index / anchoLinea;
    Gen.columna = index % anchoLinea;
    Gen.valor   = valor;

    nodos.push_back(Gen);
}

bool grafo::dentro(int fila, int columna){
    if (fila < 0) return false;
    if (columna < 0) return false;

    int totalFilas = nodos.size() / anchoLinea;
    if (fila >= totalFilas) return false;
    if (columna >= anchoLinea) return false;

    return true;
}

std::vector<struct nodo> grafo::vecinos(int fila, int columna){
    std::vector<struct nodo> vecinos;
    struct nodo aux;

    if(dentro(fila + 1, columna)) vecinos.push_back(nodos[index(fila + 1, columna)]);
    if(dentro(fila - 1, columna)) vecinos.push_back(nodos[index(fila - 1, columna)]);
    if(dentro(fila, columna + 1)) vecinos.push_back(nodos[index(fila, columna + 1)]);
    if(dentro(fila, columna - 1)) vecinos.push_back(nodos[index(fila, columna - 1)]);

    return vecinos;
}


double grafo::pesoEntre(int f1, int c1, int f2, int c2){
    if (!dentro(f1, c1)) return -1;
    if (!dentro(f2, c2)) return -1;

    int id1 = index(f1,c1);
    int id2 = index(f2,c2);

    char a = nodos[id1].valor;
    char b = nodos[id2].valor;

    double diff = std::abs(int(a) - int(b));
    return 1.0 / (1.0 + diff);
}


double grafo::pesoVecino(int fila, int columna, char dir){
    int f = fila;
    int c = columna;

    switch(dir) {
        case 'U': f--; break;
        case 'D': f++; break;
        case 'L': c--; break;
        case 'R': c++; break;
        default: return -1;
    }

    return pesoEntre(fila, columna, f, c);
}

std::vector<int> grafo::dijkstra(int f1, int c1, int f2, int c2){
    int n = nodos.size();
    int start = index(f1, c1);
    int goal  = index(f2, c2);

    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> prev(n, -1);
    std::vector<bool> inQ(n, true);

    dist[start] = 0;

    while(true){
        int u = -1;
        double minDist = std::numeric_limits<double>::infinity();
        for(int i = 0; i < n; ++i){
            if(inQ[i] && dist[i] < minDist){
                minDist = dist[i];
                u = i;
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

        std::vector<struct nodo> vs = vecinos(uf, uc);
        std::vector<struct nodo>::iterator vn = vs.begin();
        for(; vn != vs.end(); vn++){
            int v = index(vn->fila, vn->columna);

            if(!inQ[v]) continue;

            double w = pesoEntre(uf, uc, vn->fila, vn->columna);
            if(w < 0) continue;

            double alt = dist[u] + w;
            if(alt < dist[v]){
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }


    std::vector<int> camino;

    if(dist[goal] == std::numeric_limits<double>::infinity()){
        // Camino vacío = no existe
        return camino;
    }

    // reconstrucción desde goal hacia start
    int actual = goal;
    while(actual != -1){
        camino.push_back(actual);
        actual = prev[actual];
    }

    // invertir manualmente (sin std::reverse si no quieres)
    for(int i = 0; i < camino.size()/2; i++){
        int tmp = camino[i];
        camino[i] = camino[camino.size() - 1 - i];
        camino[camino.size() - 1 - i] = tmp;
    }

    return camino;
}
