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

    //Métodos
    char get_simbolo(void) {
        return simbolo;
    }

    int get_estado(void) {
        return estado;
    }
};

class AFN {
    set<int> estados;
    set<char> alfabeto;
    vector<vector<Transicion>> transcisiones;
    int estado_inicial;
    set<int> estados_aceptacion; 

public:
    //constructor
    AFN(set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion) {
        this -> estados = estados;
        this -> alfabeto = alfabeto;
        this -> estado_inicial = estado_inicial;
        this -> estados_aceptacion = estados_aceptacion;
        transcisiones.resize(estados.size());
    }

    //Métodos    
    void inserta_transicion(int origen, char simbolo, int destino) {
        //origen ---simbolo---> destino
        transcisiones[origen].push_back(Transicion(simbolo,destino));
    }

    void imprime_transiciones(void) {
        for (int i = 0; i < transcisiones.size(); i++) {
            cout << "Estando en " << i << " puedo ir a :" << endl;
            for (int j = 0; j < transcisiones[i].size(); j++) {
                cout << "\t" << transcisiones[i][j].get_estado() << " con '";
                cout << transcisiones[i][j].get_simbolo() << "'" << endl;
            } 
        }
    }
};

int main() {
    //AFN 'N' para (a|b)*abb
    set<int> estados = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    set<char> alfabeto = {'a', 'b'};
    set<int> estados_aceptacion = {10};
    AFN N = AFN(estados, alfabeto, 0, estados_aceptacion);
    N.inserta_transicion(0, 'E', 1);
    N.inserta_transicion(0, 'E', 7);
    N.inserta_transicion(1, 'E', 2);
    N.inserta_transicion(1, 'E', 4);
    N.inserta_transicion(2, 'a', 3);
    N.inserta_transicion(3, 'E', 6);
    N.inserta_transicion(4, 'b', 5);
    N.inserta_transicion(4, 'b', 5);
    N.inserta_transicion(5, 'E', 6);
    N.inserta_transicion(6, 'E', 1);
    N.inserta_transicion(6, 'E', 7);
    N.inserta_transicion(7, 'a', 8);
    N.inserta_transicion(8, 'b', 9);
    N.inserta_transicion(9, 'b', 10);
    N.imprime_transiciones();
    return 0;
}