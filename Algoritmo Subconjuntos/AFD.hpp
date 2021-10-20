#include <bits/stdc++.h>
#include "Automata.hpp"
using namespace std;

class AFD : public Automata {
public:
    //Constructores
    AFD(set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion)
        : Automata(estados, alfabeto, estado_inicial, estados_aceptacion) {
    }

    AFD(set<int> estados, set<char> alfabeto, vector<vector<Transicion>> transiciones,int estado_inicial, set<int> estados_aceptacion) 
        : Automata(estados, alfabeto, transiciones, estado_inicial, estados_aceptacion) {
    }
};