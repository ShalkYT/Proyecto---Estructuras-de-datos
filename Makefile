CXX = g++
CXXFLAGS = -Wall -std=c++17 -IDeclaracion
SOURCEDIR = Implementacion/

DEPENDENCYS = $(SOURCEDIR)Genomas.cxx $(SOURCEDIR)Secuencia.cxx $(SOURCEDIR)GestorDeGenomas.cxx

NewMain:
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) NewMain.cpp -o main

clear:
	rm -f main