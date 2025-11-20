CXX = g++
CXXFLAGS = -Wall -std=c++17 -IDeclaracion -IArbolHuffman
SOURCEDIR = Implementacion/
ARBOLDIR = ArbolHuffman/
GRAFODIR = Grafos/

DEPENDENCYS = $(SOURCEDIR)Genomas.cxx $(SOURCEDIR)Secuencia.cxx $(SOURCEDIR)GestorDeGenomas.cxx $(ARBOLDIR)arbolH.cxx $(ARBOLDIR)nodo.cxx $(GRAFODIR)grafo.cxx

NewMain:
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) NewMain.cpp -o main

clean:
	rm -f main