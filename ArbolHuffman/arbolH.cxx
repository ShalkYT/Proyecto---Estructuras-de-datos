#include "arbolH.h"
#include <queue>
#include <vector>

arbolH::arbolH(){
    raiz = nullptr;
}

arbolH::~arbolH(){
    destruirArbol(raiz);
}

void arbolH::destruirArbol(nodo* n){
    if(n != nullptr){
        destruirArbol(n->izq);
        destruirArbol(n->der);
        delete n;
    }
}

// Construye el árbol de Huffman usando una cola de prioridad (min-heap)
void arbolH::construirArbol(std::vector<struct caracter> histograma){
    if(histograma.empty()) return;
    
    // Cola de prioridad (min-heap) para construir el árbol
    // Los nodos con menor frecuencia tienen mayor prioridad
    std::priority_queue<nodo*, std::vector<nodo*>, CompararNodos> pq;
    
    // Paso 1: Insertar todos los caracteres como nodos hoja en la cola
    for(size_t i = 0; i < histograma.size(); i++){
        nodo* nuevo = new nodo(histograma[i]);
        pq.push(nuevo);
    }
    
    // Paso 2: Construir el árbol combinando los dos nodos con menor frecuencia
    while(pq.size() > 1){
        // Extraer los dos nodos con menor frecuencia
        nodo* izq = pq.top();
        pq.pop();
        nodo* der = pq.top();
        pq.pop();
        
        // Crear un nodo interno con la suma de frecuencias
        struct caracter interno;
        interno.Gen = '\0'; // Nodo interno sin carácter (marcador)
        interno.Repeticiones = izq->caracter.Repeticiones + der->caracter.Repeticiones;
        
        nodo* padre = new nodo(interno);
        padre->izq = izq;
        padre->der = der;
        
        // Insertar el nuevo nodo combinado en la cola
        pq.push(padre);
    }
    
    // El último nodo restante es la raíz del árbol
    raiz = pq.top();
}

// Genera los códigos Huffman recursivamente recorriendo el árbol
void arbolH::generarCodigos(nodo* n, std::string codigo, std::map<char, std::string>& tabla){
    if(n == nullptr) return;
    
    // Si es un nodo hoja (tiene un carácter válido)
    if(n->izq == nullptr && n->der == nullptr && n->caracter.Gen != '\0'){
        // Caso especial: si solo hay un carácter, asignarle "0"
        tabla[n->caracter.Gen] = codigo.empty() ? "0" : codigo;
        return;
    }
    
    // Recorrer el subárbol izquierdo agregando "0" al código
    generarCodigos(n->izq, codigo + "0", tabla);
    
    // Recorrer el subárbol derecho agregando "1" al código
    generarCodigos(n->der, codigo + "1", tabla);
}

// Genera la tabla completa de códigos Huffman
std::map<char, std::string> arbolH::generarTablaCodigos(){
    std::map<char, std::string> tabla;
    generarCodigos(raiz, "", tabla);
    return tabla;
}

// Codifica una secuencia completa usando los códigos Huffman
std::string arbolH::codificarSecuencia(const std::string& secuencia){
    std::map<char, std::string> tabla = generarTablaCodigos();
    std::string resultado;
    
    for(size_t i = 0; i < secuencia.length(); i++){
        if(tabla.find(secuencia[i]) != tabla.end()){
            resultado += tabla[secuencia[i]];
        }
    }
    
    return resultado;
}

// Decodifica una secuencia binaria usando el árbol de Huffman
std::string arbolH::decodificarSecuencia(const std::string& codigoBinario){
    std::string resultado;
    nodo* actual = raiz;
    
    for(size_t i = 0; i < codigoBinario.length(); i++){
        if(actual == nullptr) break;
        
        // Navegar por el árbol según el bit
        if(codigoBinario[i] == '0'){
            actual = actual->izq;
        } else if(codigoBinario[i] == '1'){
            actual = actual->der;
        }
        
        // Si llegamos a una hoja, añadir el carácter y volver a la raíz
        if(actual != nullptr && actual->izq == nullptr && actual->der == nullptr){
            resultado += actual->caracter.Gen;
            actual = raiz; // Reiniciar para el siguiente carácter
        }
    }
    
    return resultado;
}

// Obtiene el histograma recorriendo el árbol (útil para debugging)
std::vector<struct caracter> arbolH::obtenerHistograma(){
    std::vector<struct caracter> histograma;
    std::queue<nodo*> cola;
    
    if(raiz != nullptr){
        cola.push(raiz);
    }
    
    // Recorrido por niveles (BFS)
    while(!cola.empty()){
        nodo* actual = cola.front();
        cola.pop();
        
        // Si es una hoja (tiene carácter válido), añadir al histograma
        if(actual->izq == nullptr && actual->der == nullptr && actual->caracter.Gen != '\0'){
            histograma.push_back(actual->caracter);
        }
        
        if(actual->izq != nullptr) cola.push(actual->izq);
        if(actual->der != nullptr) cola.push(actual->der);
    }
    
    return histograma;
}