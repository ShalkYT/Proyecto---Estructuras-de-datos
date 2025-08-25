CXX = g++
CXXFLAGS = -Wall -std=c++17

# No es utilizado actualmente
# DEPENDENCYS = 
PROGRAMS = main
# all: $(PROGRAMS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPENDENCYS) main.cpp -o main

clear:
	rm -f $(PROGRAMS)