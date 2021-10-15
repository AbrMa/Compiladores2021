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

    //Métodos
    char get_simbolo(void) {
        return simbolo;
    }

    int get_estado(void) {
        return estado;
    }
};

class Destado {
    set<int> conjunto;
    bool marcado;

public:
    //Constructor
    Destado(set<int> conjunto, bool marcado) {
        this -> conjunto = conjunto;
        this -> marcado = marcado;
    }

    //Métodos
    void set_conjunto(set<int> conjunto) {
        this -> conjunto = conjunto;
    }

    void set_marcado(bool marcado) {
        this -> marcado = marcado;
    }

    set<int> get_conjunto(void) {
        return conjunto;
    }

    bool get_marcado(void) {
        return marcado;
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

    //Cerradura-épsilon(s)
    set<int> cerradura_epsilon(int estado) {
        set<int> conjunto;
        vector<bool> visitado(transcisiones.size(), false);
        dfs(estado, conjunto, visitado);
        return conjunto;
    }

    //Función auxiliar para hacer recorridos en el grafo
    void dfs(int estado, set<int> &conjunto, vector<bool> &visitado) {
        //Caso base
        if (visitado[estado]) {
            return;
        }

        visitado[estado] = true;
        conjunto.insert(estado);

        for (Transicion destino : transcisiones[estado]) {
            if (destino.get_simbolo() == 'E') {
                dfs(destino.get_estado(), conjunto, visitado);
            }
        }
    }

    //Mover(T,a)
    set<int> mover(set<int> T, char simbolo) {
        set<int> conjunto;
        for (int elemento : T) {
            for (Transicion destino : transcisiones[elemento]) {
                if (destino.get_simbolo() == simbolo) {
                    conjunto.insert(destino.get_estado());
                }
            }
        }
        return conjunto;
    }

    void subconjuntos(void) {
        set<set<int>> d_estados;
        vector<bool> visitado(1,false);
        d_estados.insert(cerradura_epsilon(estado_inicial));
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
    //N.imprime_transiciones();
    set<int> T = N.cerradura_epsilon(6);
    set<int> mover = N.mover({1,2,3,4,6,7,8},'b');
    /*
    for (auto r : mover) {
        cout << r << endl;
    }
    */
    return 0;
}