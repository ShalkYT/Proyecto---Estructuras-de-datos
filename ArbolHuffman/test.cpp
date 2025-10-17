#include <iostream>
#include "arbolH.h"

int main(){

    arbolH miArbol;

    std::cout << "Pruebas nodo.cpp" << std::endl;

    miArbol.insertar({'a', 5});
    miArbol.insertar({'b', 3});
    miArbol.insertar({'c', 8});
    miArbol.insertar({'d', 1});

    std::cout << "Recorrido inOrden del arbol:" << std::endl;
    miArbol.inOrden();

    char caracterACodificar = 'd';
    std::string codigo = miArbol.codificar(caracterACodificar);
    std::cout << "Codigo de '" << caracterACodificar << "': " << codigo << std::endl;

    std::string codigoADecodificar = "001";
    char caracterDecodificado = miArbol.decodificar(codigoADecodificar);
    std::cout << "Caracter decodificado de '" << codigoADecodificar << "': " << caracterDecodificado << std::endl;

    return 0;
}