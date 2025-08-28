CXX = g++
CXXFLAGS = -Wall -std=c++17

# No es utilizado actualmente
DEPENDENCYS = Genomas.cxx Secuencia.cxx GestorDeGenomas.cxx

NewMain:
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) NewMain.cpp -o main

clear:
	rm -f main