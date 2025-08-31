#include "Genomas.h"

void Genomas::SetGenoma(std::deque<char> Genomas){
    this->Genomas = Genomas;
}

std::deque<char> Genomas::GetGenomas(){
    return Genomas;
}

int Genomas::ContarBases(){
    std::deque<char>::iterator it;
    int Count = 0;
    for(it = Genomas.begin(); it != Genomas.end(); it++){
        if(*(it) == 'A' || *(it) == 'C' || *(it) == 'G' || *(it) == 'T' || *(it) == 'U' || *(it) == '-' ){
            Count++;
        }
    }
    return Count;
}

bool Genomas::EsCompleta(){
    std::deque<char>::iterator it;
    bool Completa = true;
    for(it = Genomas.begin(); it != Genomas.end(); it++){
        if(*(it) != 'A' || *(it) != 'C' || *(it) != 'G' || *(it) != 'T' || *(it) != 'U') {
            Completa = false;
        }
    }
    return Completa;
}

std::vector<int> Genomas::ConteoHistograma(){
    std::vector<int> Count(6,0);
    std::vector<int>::iterator it = Count.begin();
    std::deque<char>::iterator it2;
    for(it2 = Genomas.begin(); it2 != Genomas.end(); it2++){
        if(*(it2) == 'A') (*(it))++;
        if(*(it2) == 'C') (*(it + 1))++;
        if(*(it2) == 'G') (*(it + 2))++;
        if(*(it2) == 'T') (*(it + 3))++;
        if(*(it2) == 'U') (*(it + 4))++;
        if(*(it2) == '-') (*(it + 5))++;
    } 
    return Count;
}

int Genomas::Cantidad_Subsecuencias(std::string Subsecuencia){
    int Count = 0;
    bool Es_Subsecuencia;
    std::deque<char>::iterator itGen;
    std::deque<char>::iterator itSubGen;
    std::string::iterator itSubsecuencia;
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin();
        if(*(itGen) == *(itSubsecuencia)){
            itSubGen = itGen;
            while((itSubGen != Genomas.end() && itSubsecuencia != Subsecuencia.end())){
                if((*itSubGen) != (*itSubsecuencia)){
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
        }

    }

    return Count;
}

int Genomas::Enmascarar_Subsecuencias(std::string Subsecuencia){
    int Count = 0;
    bool Es_Subsecuencia;
    std::deque<char>::iterator itGen;
    std::deque<char>::iterator itSubGen;
    std::string::iterator itSubsecuencia;
    
    for(itGen = Genomas.begin(); itGen != Genomas.end(); itGen++){
        Es_Subsecuencia = true;
        itSubsecuencia = Subsecuencia.begin();
        if(*(itGen) == *(itSubsecuencia)){
            itSubGen = itGen;
            while((itSubGen != Genomas.end() && itSubsecuencia != Subsecuencia.end())){
                if((*itSubGen) != (*itSubsecuencia)){
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