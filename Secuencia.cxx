#include "Secuencia.h"
#include <iostream>

void Secuencia::AñadirGenomas(std::deque<char> Genoma){ // Método que recibe un genoma como deque de caracteres
    Genomas G; // Crea un objeto de tipo Genomas
    G.SetGenoma(Genoma); // Asigna el genoma recibido al objeto G
    VectorGenomas.push_back(G); // Agrega el objeto G al vector de genomas
}

void Secuencia::SetNombre(std::string Nombre){ // Método que recibe un nombre como string
    this->Nombre = Nombre; // Asigna el valor recibido al atributo Nombre del objeto
}

std::string Secuencia::GetNombre(){ // Método que devuelve el nombre de la secuencia
    return Nombre; // Retorna el atributo Nombre
}

std::vector<Genomas> Secuencia::GetGenomas(){ // Método que devuelve el vector de genomas
    return VectorGenomas; // Retorna el atributo VectorGenomas
}

long long Secuencia::ContarBases(){ // Método que cuenta el total de bases en todos los genomas
    long long Count = 0; // Inicializa el contador en 0

    std::vector<Genomas>::iterator it; // Declara un iterador para recorrer el vector de genomas
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma en el vector
        Count += it->ContarBases(); // Suma al contador las bases del genoma actual
    }

    return Count; // Retorna el total de bases contadas
}


bool Secuencia::GenomasCompletos(){ // Método que verifica si todos los genomas están completos
    bool Completos = true; // Se asume inicialmente que todos están completos

    std::vector<Genomas>::iterator it; // Declara un iterador para recorrer el vector de genomas
    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma en el vector
        if(!(it->EsCompleta())){ // Si el genoma actual no está completo
            Completos = false; // Marca la variable como falso
        }
    }

    return Completos; // Retorna si todos los genomas están completos o no
}

std::vector<int> Secuencia::histogramaSecuencia(){ // Método que genera un histograma acumulado de la secuencia
    std::vector<int> Count(18,0); // Inicializa un vector de 18 posiciones en cero
    std::vector<int>::iterator itHistograma = Count.begin(); // Iterador al inicio del histograma
    std::vector<Genomas>::iterator itGenomas; // Iterador para recorrer los genomas
    for(itGenomas = VectorGenomas.begin(); itGenomas != VectorGenomas.end(); itGenomas++){ // Recorre cada genoma
        std::vector<int> temp = itGenomas->ConteoHistograma(); // Obtiene el histograma del genoma actual
        std::vector<int>::iterator aux = temp.begin(); // Iterador al inicio del histograma temporal
        *(itHistograma) += *(aux); // Suma la primera posición
        *(itHistograma + 1) += *(aux + 1); // Suma la segunda posición
        *(itHistograma + 2) += *(aux + 2); // Suma la tercera posición
        *(itHistograma + 3) += *(aux + 3); // Suma la cuarta posición
        *(itHistograma + 4) += *(aux + 4); // Suma la quinta posición
        *(itHistograma + 5) += *(aux + 5); // Suma la sexta posición
        *(itHistograma + 6) += *(aux + 6); // Suma la séptima posición
        *(itHistograma + 7) += *(aux + 7); // Suma la octava posición
        *(itHistograma + 8) += *(aux + 8); // Suma la novena posición
        *(itHistograma + 9) += *(aux + 9); // Suma la décima posición
        *(itHistograma + 10) += *(aux + 10); // Suma la posición 11
        *(itHistograma + 11) += *(aux + 11); // Suma la posición 12
        *(itHistograma + 12) += *(aux + 12); // Suma la posición 13
        *(itHistograma + 13) += *(aux + 13); // Suma la posición 14
        *(itHistograma + 14) += *(aux + 14); // Suma la posición 15
        *(itHistograma + 15) += *(aux + 15); // Suma la posición 16
        *(itHistograma + 16) += *(aux + 16); // Suma la posición 17
        *(itHistograma + 17) += *(aux + 17); // Suma la posición 18
    }
    return Count; // Retorna el histograma acumulado
}

int Secuencia::Cantidad_Subsecuencias(std::string Subsecuencia){ // Método que cuenta las apariciones de una subsecuencia
    std::vector<Genomas>::iterator it; // Iterador para recorrer los genomas
    int Contador = 0; // Inicializa contador en 0

    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma
        Contador += it->Cantidad_Subsecuencias(Subsecuencia); // Suma las apariciones de la subsecuencia en cada genoma
    }

    return Contador; // Retorna la cantidad total de apariciones
}

int Secuencia::Enmascarar_Subsecuencias(std::string Subsecuencia){ // Método que enmascara una subsecuencia en todos los genomas
    std::vector<Genomas>::iterator it; // Iterador para recorrer los genomas
    int Contador = 0; // Inicializa contador en 0

    for(it = VectorGenomas.begin(); it != VectorGenomas.end(); it++){ // Recorre cada genoma
        Contador += it->Enmascarar_Subsecuencias(Subsecuencia); // Suma las veces que se enmascaró la subsecuencia
    }

    return Contador; // Retorna la cantidad total de subsecuencias enmascaradas
}