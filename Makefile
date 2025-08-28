CXX = g++
CXXFLAGS = -Wall -std=c++17

DEPENDENCYS = Genomas.cxx Secuencia.cxx GestorDeGenomas.cxx

NewMain:
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) NewMain.cpp -o main

clear:
	rm -f main