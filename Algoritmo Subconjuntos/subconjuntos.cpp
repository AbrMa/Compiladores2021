/*
    Descripción : 
        La construcción de subconjuntos de un AFD, a partir de un AFN.

    Entrada:
        Un AFN 'N'.

    Salida:
        Un AFD 'D' que acepta el mismo lenguaje que N.    
*/
#include <bits/stdc++.h>
using namespace std;

class Transicion {
    char simbolo;
    int estado;

public:
    //Constructores
    Transicion(char simbolo, int estado) {
        this -> simbolo = simbolo;
        this -> estado = estado;
    }    
    Transicion(int estado, int simbolo) {
        this -> simbolo = simbolo;
        this -> estado = estado;
    }    
};

int main() {
    //AFN 'N' para (a|b)*abb
    vector<vector<Transicion>> N(11);
    N[0].push_back(Transicion('E', 1)); 
    N[0].push_back(Transicion('E', 7)); 
    N[1].push_back(Transicion('E', 2)); 
    N[1].push_back(Transicion('E', 4)); 
    N[2].push_back(Transicion('a', 3)); 
    N[3].push_back(Transicion('E', 6)); 
    N[4].push_back(Transicion('b', 5)); 
    N[5].push_back(Transicion('E', 6)); 
    N[6].push_back(Transicion('E', 7)); 
    N[6].push_back(Transicion('E', 1)); 
    N[7].push_back(Transicion('a', 8)); 
    N[8].push_back(Transicion('b', 9)); 
    N[9].push_back(Transicion('b', 10)); 

    return 0;
}