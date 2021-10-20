#include <bits/stdc++.h>
#include "Transicion.hpp"

using namespace std;

class Automata {
private:
    set<int> estados;
    set<char> alfabeto;
    vector<vector<Transicion>> transiciones;
    int estado_inicial;
    set<int> estados_aceptacion;

public:
    //constructores
    Automata(set<int> estados, set<char> alfabeto, vector<vector<Transicion>> transiciones,int estado_inicial, set<int> estados_aceptacion) {
        this->estados = estados;
        this->alfabeto = alfabeto;
        this->transiciones = transiciones;
        this->estado_inicial = estado_inicial;
        this->estados_aceptacion = estados_aceptacion;
    }

    Automata(set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion) {
        this->estados = estados;
        this->alfabeto = alfabeto;
        this->estado_inicial = estado_inicial;
        this->estados_aceptacion = estados_aceptacion;
        transiciones.resize(estados.size());
    }

    //Métodos
    set<int> get_estados(void) {
        return estados;
    }

    set<char> get_alfabeto(void) {
        return alfabeto;
    }

    vector<vector<Transicion>> get_transiciones(void) {
        return transiciones;
    }

    int get_estado_inicial(void) {
        return estado_inicial;
    }

    set<int> get_estados_aceptacion(void) {
        return estados_aceptacion;
    }

    virtual void inserta_transicion(int origen, char simbolo, int destino) {
        //origen ---simbolo---> destino
        transiciones[origen].push_back(Transicion(simbolo, destino));
    }

    void imprime_transiciones(void) {
        cout << "digraph automata { \n";

        cout << "\trankdir = LR;\n\tnode [shape = doublecircle]; ";
        for (int elemento : estados_aceptacion) {
            cout << elemento << " ";
        }
        cout << "\n\tnode [shape = point ]; inicial;\n";
        cout << "\n\tnode [shape = circle];\n";
        cout << "inicial -> 0;\n";
        for (int i = 0; i < transiciones.size(); i++) {
            for (int j = 0; j < transiciones[i].size(); j++) {
                cout << "\t" << i << " -> " << transiciones[i][j].get_estado() << " [label = \"";
                cout << transiciones[i][j].get_simbolo() << "\"];" << endl;
            }
        }
        cout << "}";
        cout << endl;
    }

    void escribe_archivo(ofstream &archivo) {
        archivo << "digraph automata { \n";

        archivo << "\trankdir = LR;\n\tnode [shape = doublecircle]; ";
        for (int elemento : estados_aceptacion) {
            archivo << elemento << " ";
        }
        archivo << "\n\tnode [shape = point ]; inicial;\n";
        archivo << "\n\tnode [shape = circle];\n";
        archivo << "inicial -> 0;\n";
        for (int i = 0; i < transiciones.size(); i++) {
            for (int j = 0; j < transiciones[i].size(); j++) {
                archivo << "\t" << i << " -> " << transiciones[i][j].get_estado() << " [label = \"";
                archivo << transiciones[i][j].get_simbolo() << "\"];" << endl;
            }
        }
        archivo << "}";
        archivo << endl;
    }
};