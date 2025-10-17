#include "arbolH.h"

arbolH::arbolH(){
    raiz = nullptr;
}

void arbolH::insertar(nodo* &n, struct caracter c){
    if (n == nullptr){
        n = new nodo(c);
        return;
    }

    if(n->izq == nullptr){
        insertar(n->izq, c);
        return;
    }
    if(n->der == nullptr){
        insertar(n->der, c);
        return;
    }
    
    if(c.Repeticiones < n->caracter.Repeticiones){
        insertar(n->izq, c);
    } else {
        insertar(n->der, c);
    }
}

void arbolH::insertar(struct caracter c){
    insertar(raiz, c);
}

void arbolH::inOrden(nodo* n){
    if(n == nullptr){
        return;
    }else{
        inOrden(n->izq);
        std::cout << n->caracter.Gen << " : " << n->caracter.Repeticiones << std::endl;
        inOrden(n->der);
    }
}

void arbolH::inOrden(){
    inOrden(raiz);
}

std::string arbolH::codificar(nodo* n, char c){
    if(n == nullptr){
        return "";
    }

    if(n->caracter.Gen == c){
        return " ";
    }

    std::string caminoIzquierdo = codificar(n->izq, c);
    if(!caminoIzquierdo.empty() || (n->izq != nullptr && n->izq->caracter.Gen == c)){
        return "0" + caminoIzquierdo;
    }

    std::string caminoDerecho = codificar(n->der, c);
    if(!caminoDerecho.empty() || (n->der != nullptr && n->der->caracter.Gen == c)){
        return "1" + caminoDerecho;
    }

    return "";
}

std::string arbolH::codificar(char c){
    return codificar(raiz, c);
}

char arbolH::decodificar(nodo* n, std::string codigo){
    int i;
    for(i = sizeof(codigo); i >= 0; i--){
        if(n == nullptr){
            return '\0';
        }
        if(codigo[i] == '0'){
            n = n->izq;
        } else if(codigo[i] == '1'){
            n = n->der;
        }
    }
    return n->caracter.Gen;
}

char arbolH::decodificar(std::string codigo){
    return decodificar(raiz, codigo);
}