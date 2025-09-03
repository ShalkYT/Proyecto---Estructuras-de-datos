#include "Genomas.h"
#include <iostream>

void Genomas::SetGenoma(std::deque<char> Genomas){
    this->Genomas = Genomas;
}

std::deque<char> Genomas::GetGenomas(){
    return Genomas;
}

long long Genomas::ContarBases(){
    std::deque<char>::iterator it;
    long long Count = 0;
    for(it = Genomas.begin(); it != Genomas.end(); it++){
        if(*(it) == 'A' || *(it) == 'C' || *(it) == 'G' || *(it) == 'T' || *(it) == 'U' ){
            Count++;
        }
    }
    return Count;
}

bool Genomas::EsCompleta(){
    std::deque<char>::iterator it;
    bool Completa = true;
    for(it = Genomas.begin(); it != Genomas.end(); it++){
        if(*(it) != 'A' && *(it) != 'C' && *(it) != 'G' && *(it) != 'T' && *(it) != 'U') {
            Completa = false;
        }
    }
    return Completa;
}

std::vector<int> Genomas::ConteoHistograma(){
    std::vector<int> Count(18,0);
    std::vector<int>::iterator it = Count.begin();
    std::deque<char>::iterator it2;
    for(it2 = Genomas.begin(); it2 != Genomas.end(); it2++){
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
    return Count;
}

bool Genomas::coincide_con_patron(char codigo_busqueda, char caracter_genoma) {
    codigo_busqueda = std::toupper(codigo_busqueda);
    caracter_genoma = std::toupper(caracter_genoma);
    
    // 1. Si son IGUALES: siempre true
    if (codigo_busqueda == caracter_genoma) {
        return true;
    }
    
    // 2. Manejar caracteres AMBIGUOS en el genoma
    switch(caracter_genoma) {
        case 'R': 
            return (codigo_busqueda == 'A' || codigo_busqueda == 'G');
        case 'Y':
            return (codigo_busqueda == 'C' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'K':
            return (codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'M':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'C');
        case 'S':
            return (codigo_busqueda == 'C' || codigo_busqueda == 'G');
        case 'W':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'B':
            return (codigo_busqueda == 'C' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'D':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'H':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        case 'V':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'G');
        case 'N':
            return (codigo_busqueda == 'A' || codigo_busqueda == 'C' || codigo_busqueda == 'G' || codigo_busqueda == 'T' || codigo_busqueda == 'U');
        default: break;
    }
    
    // 3. Manejar códigos de búsqueda NORMALES
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

int Genomas::Cantidad_Subsecuencias(std::string Subsecuencia){
    if(Subsecuencia.empty() || Genomas.empty()) return 0;
   
    int Count = 0;
    bool Es_Subsecuencia;
    std::deque<char>::iterator itGen;
    std::deque<char>::iterator itSubGen;
    std::string::iterator itSubsecuencia;
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin();
        itSubGen = itGen;
        
        while((itSubsecuencia != Subsecuencia.end() && itSubGen != Genomas.end())){
            if(!coincide_con_patron(*itSubsecuencia, *itSubGen)){
                Es_Subsecuencia = false;
                break;
            }
            itSubGen++;
            itSubsecuencia++;
        }

        if(Es_Subsecuencia && itSubsecuencia == Subsecuencia.end()){
            Count++;
        }
    }
    
    return Count;
}
int Genomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    if(Subsecuencia.empty() || Genomas.empty()) return 0;
    
    int Count = 0;
    bool Es_Subsecuencia;
    std::deque<char>::iterator itGen;
    std::deque<char>::iterator itSubGen;
    std::string::iterator itSubsecuencia;
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin();
        
        
        if(coincide_con_patron(*itSubsecuencia, *itGen)){  
            itSubGen = itGen;
            while((itSubGen != Genomas.end() && itSubsecuencia != Subsecuencia.end())){
            
                if(!coincide_con_patron(*itSubsecuencia, *itSubGen)){
                    Es_Subsecuencia = false;
                    break;
                }
                itSubGen++;
                itSubsecuencia++;
            }
        }else{
            Es_Subsecuencia = false;
        }

        if(Es_Subsecuencia && itSubsecuencia == Subsecuencia.end()){
            Count++;
            itSubGen = itGen;
            for(itSubsecuencia = Subsecuencia.begin(); itSubsecuencia != Subsecuencia.end(); itSubsecuencia++){
                *(itSubGen) = 'X';
                itSubGen++;
            }
        }
    }

    return Count;
}