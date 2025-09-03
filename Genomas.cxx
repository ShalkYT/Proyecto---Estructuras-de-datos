// ===================================================================================
// File:                   Genomas.cpp
// Autor:                  Andres Meneses, Brandon Garcia, Andres Beltran
// Fecha de entrega:       2025-09-03
// Descripción:            Implementación de los métodos de la clase Genomas.
// ===================================================================================

#include "Genomas.h"
#include <iostream>

// Asigna un genoma completo a partir de un deque de caracteres.
void Genomas::SetGenoma(std::deque<char> Genomas){
    this->Genomas = Genomas;
}

// Devuelve el genoma almacenado como un deque de caracteres.
std::deque<char> Genomas::GetGenomas(){
    return Genomas;
}

// Cuenta cuántas bases válidas (A, C, G, T, U) existen en el genoma.
long long Genomas::ContarBases(){
    std::deque<char>::iterator it; // Iterador sobre el deque de genoma
    long long Count = 0; // Contador de bases
    for(it = Genomas.begin(); it != Genomas.end(); it++){ // Recorre todos los caracteres
        if(*(it) == 'A' || *(it) == 'C' || *(it) == 'G' || *(it) == 'T' || *(it) == 'U' ){
            Count++; // Suma al contador si es una base válida
        }
    }
    return Count; // Devuelve el total de bases válidas
}

// Verifica si el genoma está compuesto únicamente por bases válidas.
bool Genomas::EsCompleta(){
    std::deque<char>::iterator it; // Iterador del genoma
    bool Completa = true; // Supone inicialmente que está completo
    for(it = Genomas.begin(); it != Genomas.end(); it++){ // Recorre cada carácter
        if(*(it) != 'A' && *(it) != 'C' && *(it) != 'G' && *(it) != 'T' && *(it) != 'U') {
            Completa = false; // Si encuentra un carácter inválido, marca como incompleto
        }
    }
    return Completa; // Devuelve el resultado final
}

// Genera un histograma de 18 categorías con la frecuencia de cada carácter posible en el genoma.
std::vector<int> Genomas::ConteoHistograma(){
    std::vector<int> Count(18,0); // Inicializa vector de 18 contadores en cero
    std::vector<int>::iterator it = Count.begin(); // Iterador para recorrer posiciones del histograma
    std::deque<char>::iterator it2; // Iterador sobre el genoma

    for(it2 = Genomas.begin(); it2 != Genomas.end(); it2++){ // Recorre cada carácter del genoma
        if(*(it2) == 'A') (*(it))++;
        if(*(it2) == 'C') (*(it + 1))++;
        if(*(it2) == 'G') (*(it + 2))++;
        if(*(it2) == 'T') (*(it + 3))++;
        if(*(it2) == 'U') (*(it + 4))++;
        if(*(it2) == 'R') (*(it + 5))++;
        if(*(it2) == '-') (*(it + 6))++;
        if(*(it2) == 'Y') (*(it + 7))++;
        if(*(it2) == 'K') (*(it + 8))++;
        if(*(it2) == 'M') (*(it + 9))++;
        if(*(it2) == 'S') (*(it + 10))++;
        if(*(it2) == 'W') (*(it + 11))++;
        if(*(it2) == 'B') (*(it + 12))++;
        if(*(it2) == 'D') (*(it + 13))++;
        if(*(it2) == 'H') (*(it + 14))++;
        if(*(it2) == 'V') (*(it + 15))++;
        if(*(it2) == 'N') (*(it + 16))++;
        if(*(it2) == 'X') (*(it + 17))++;
    } 
    return Count; // Devuelve el histograma generado
}

// Determina si un carácter de búsqueda coincide con un carácter del genoma, considerando casos ambiguos.
bool Genomas::coincide_con_patron(char codigo_busqueda, char caracter_genoma) {
    codigo_busqueda = std::toupper(codigo_busqueda); // Convierte a mayúscula el código de búsqueda
    caracter_genoma = std::toupper(caracter_genoma); // Convierte a mayúscula el carácter del genoma
    
    // 1. Coincidencia exacta
    if (codigo_busqueda == caracter_genoma) {
        return true;
    }
    
    // 2. Coincidencias con caracteres ambiguos en el genoma
    switch(caracter_genoma) {
        case 'R': return (codigo_busqueda == 'A' || codigo_busqueda == 'G');
        case 'Y': return (codigo_busqueda == 'C' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'K': return (codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'M': return (codigo_busqueda == 'A' || codigo_busqueda == 'C');
        case 'S': return (codigo_busqueda == 'C' || codigo_busqueda == 'G');
        case 'W': return (codigo_busqueda == 'A' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'B': return (codigo_busqueda == 'C' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'D': return (codigo_busqueda == 'A' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'H': return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'V': return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'G');
        case 'N': return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        default: break;
    }
    
    // 3. Coincidencias directas con caracteres normales
    switch(codigo_busqueda) {
        case 'A': return (caracter_genoma == 'A');
        case 'C': return (caracter_genoma == 'C');
        case 'G': return (caracter_genoma == 'G');
        case 'T': return (caracter_genoma == 'T');
        case 'U': return (caracter_genoma == 'U');
        case 'X': return (caracter_genoma == 'X');
        case '-': return (caracter_genoma == '-');
        default: return false;
    }
}

// Cuenta cuántas veces aparece una subsecuencia dentro del genoma.
int Genomas::Cantidad_Subsecuencias(std::string Subsecuencia){
    if(Subsecuencia.empty() || Genomas.empty()) return 0; // Si no hay nada que buscar, devuelve 0
   
    int Count = 0; // Contador de apariciones
    bool Es_Subsecuencia; // Marca si se encontró una subsecuencia completa
    std::deque<char>::iterator itGen; // Iterador sobre el genoma
    std::deque<char>::iterator itSubGen; // Iterador de avance en el genoma
    std::string::iterator itSubsecuencia; // Iterador sobre la subsecuencia
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){ // Recorre el genoma desde cada posición
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin(); // Empieza desde el inicio de la subsecuencia
        itSubGen = itGen; // Comienza desde la posición actual en el genoma
        
        while((itSubsecuencia != Subsecuencia.end() && itSubGen != Genomas.end())){ // Compara mientras queden caracteres
            if(!coincide_con_patron(*itSubsecuencia, *itSubGen)){ // Si no coincide, descarta
                Es_Subsecuencia = false;
                break;
            }
            itSubGen++; // Avanza en el genoma
            itSubsecuencia++; // Avanza en la subsecuencia
        }

        if(Es_Subsecuencia && itSubsecuencia == Subsecuencia.end()){ // Si coincidió toda la subsecuencia
            Count++;
        }
    }
    
    return Count; // Devuelve el número total de apariciones
}

// Busca y reemplaza (enmascara) todas las ocurrencias de una subsecuencia con 'X'.
int Genomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    if(Subsecuencia.empty() || Genomas.empty()) return 0; // Si no hay nada que buscar, devuelve 0
    
    int Count = 0; // Contador de ocurrencias enmascaradas
    bool Es_Subsecuencia; // Marca si una subsecuencia coincide
    std::deque<char>::iterator itGen; // Iterador del genoma
    std::deque<char>::iterator itSubGen; // Iterador auxiliar dentro del genoma
    std::string::iterator itSubsecuencia; // Iterador de la subsecuencia
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){ // Recorre cada posición del genoma
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin(); // Reinicia subsecuencia en cada inicio
        
        if(coincide_con_patron(*itSubsecuencia, *itGen)){ // Si el primer carácter coincide
            itSubGen = itGen;
            while((itSubGen != Genomas.end() && itSubsecuencia != Subsecuencia.end())){ // Compara toda la subsecuencia
                if(!coincide_con_patron(*itSubsecuencia, *itSubGen)){ // Si falla, descarta
                    Es_Subsecuencia = false;
                    break;
                }
                itSubGen++;
                itSubsecuencia++;
            }
        }else{
            Es_Subsecuencia = false; // No coincidió desde el inicio
        }

        if(Es_Subsecuencia && itSubsecuencia == Subsecuencia.end()){ // Si toda la subsecuencia coincide
            Count++; // Cuenta la aparición
            itSubGen = itGen;
            for(itSubsecuencia = Subsecuencia.begin(); itSubsecuencia != Subsecuencia.end(); itSubsecuencia++){
                *(itSubGen) = 'X'; // Reemplaza el carácter por 'X'
                itSubGen++;
            }
        }
    }

    return Count; // Devuelve la cantidad de subsecuencias enmascaradas
}