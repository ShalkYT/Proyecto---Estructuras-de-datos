#include "nodo.h"

nodo::nodo(char car){
    caracter = car;
    izq = nullptr;
    der = nullptr;
    altura = 0;
}

void nodo::actualizarAltura(){
    int altIzq = -1;
    int altDer = -1;
    
    if (izq != nullptr) {
        altIzq = izquierda->altura;
    }
    
    if (der != nullptr) {
        altDer = derecha->altura;
    }
    
    altura = 1 + std::max(altIzq, altDer);
}