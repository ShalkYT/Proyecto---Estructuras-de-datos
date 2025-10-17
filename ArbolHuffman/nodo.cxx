#include "nodo.h"

nodo::nodo(struct caracter car){
    caracter = car;
    izq = nullptr;
    der = nullptr;
    altura = 0;
}

void nodo::actualizarAltura(){
    int altIzq = -1;
    int altDer = -1;
    
    if (izq != nullptr) {
        altIzq = izq->altura;
    }
    
    if (der != nullptr) {
        altDer = der->altura;
    }
    
    altura = 1 + std::max(altIzq, altDer);
}