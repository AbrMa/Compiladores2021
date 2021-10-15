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
    Transicion(char simbolo, int estado) {
        this -> simbolo = simbolo;
        this -> estado = estado;
    }    
};

int main() {
    //AFN 'N' para (a|b)*abb

    vector<vector<Transicion>> N(11);
    N[0].push_back(Transicion('E', 1)); 
    return 0;
}