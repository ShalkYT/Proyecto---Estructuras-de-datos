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

resultadoDijkstra grafo::dijkstra(int f1, int c1){

    resultadoDijkstra resultado;

    int n = nodos.size();
    int start = index(f1, c1);
    

    std::vector<float> dist(n, std::numeric_limits<float>::infinity());
    std::vector<int> prev(n, -1);
    std::vector<bool> inQ(n, true);

    dist[start] = 0;

    while(true){
        int u = -1;
        float minDist = std::numeric_limits<float>::infinity();

        // Seleccionar el nodo con menor distancia dist[] que aún está en la cola
        for(int i = 0; i < n; i++){
            if(inQ[i] && dist[i] < minDist){
                u = i;
                minDist = dist[i];
            }
        }

        // Si no se encontró ningún nodo pendiente, se termina
        if(u == -1) break;

        inQ[u] = false;

        int uf = nodos[u].fila;
        int uc = nodos[u].columna;

        // vecinos

        std::vector<nodo_> vec = vecinos(uf, uc);
        for(std::vector<nodo_>::iterator it = vec.begin(); it != vec.end(); ++it){
            nodo_ vn = *it;

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

    resultado.dist = dist;
    resultado.prev = prev;

    return resultado;

}

ResultadoRuta grafo::ruta_mas_corta(int f1, int c1, int f2, int c2){

    ResultadoRuta resultado;
    if (!dentro(f1, c1)){
        resultado.bases[0] = '1';
        return resultado;
    }
    if (!dentro(f2, c2)){
        resultado.bases[1] = '1';
        return resultado;
    }

    resultadoDijkstra dijk = dijkstra(f1,c1);

    int start = index(f1,c1);
    int goal  = index(f2, c2);

    resultado.bases[0] = (nodos[start]).valor;
    resultado.bases[1] = (nodos[goal]).valor;

    if(dijk.dist[goal] == std::numeric_limits<float>::infinity())
        return resultado;

    resultado.costo = dijk.dist[goal];

    std::vector<int> camino;
    int actual = goal;

    while(actual != -1){
        camino.push_back(actual);
        actual = dijk.prev[actual];
    }

    // invertir
    for(int i = 0; i < (int)camino.size()/2; i++){
        int tmp = camino[i];
        camino[i] = camino[camino.size()-1-i];
        camino[camino.size()-1-i] = tmp;
    }

    resultado.a = f2;
    resultado.b = c2;
    resultado.ancho = anchoLinea;

    resultado.camino = camino;
    return resultado;
}

ResultadoRuta grafo::base_remota(int f1, int c1){

    ResultadoRuta resultado;
    if (!dentro(f1, c1)){
        resultado.bases[0] = '1';
        return resultado;
    }

    resultadoDijkstra dijk = dijkstra(f1, c1);

    int start = index(f1, c1);
    char base = nodos[start].valor;
    int dist_max = 0;
    int index_max = start;

    for(std::size_t i = 0; i < nodos.size(); i++){
        if(nodos[i].valor != base) continue;

        if(dist_max < dijk.dist[i]){
            dist_max = dijk.dist[i];
            index_max = i;
        }
    }

    int f2 = index_max / anchoLinea;
    int c2 = index_max % anchoLinea;

    return ruta_mas_corta(f1,c1,f2,c2);
}

void grafo::imprimir() {
    for(int f = 0; f < (int)longFila.size(); f++){
        for(int c = 0; c < longFila[f]; c++){
            std::cout << nodos[index(f, c)].valor << " ";
        }
        std::cout << "\n";
    }
}
