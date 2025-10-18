CXX = g++
CXXFLAGS = -Wall -std=c++17 -IDeclaracion -IArbolHuffman
SOURCEDIR = Implementacion/
ARBOLDIR = ArbolHuffman/

DEPENDENCYS = $(SOURCEDIR)Genomas.cxx $(SOURCEDIR)Secuencia.cxx $(SOURCEDIR)GestorDeGenomas.cxx $(ARBOLDIR)arbolH.cxx $(ARBOLDIR)nodo.cxx

NewMain:
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) NewMain.cpp -o main

clear:
	rm -f main