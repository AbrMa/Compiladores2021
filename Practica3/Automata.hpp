#include <bits/stdc++.h>
#include "Transicion.hpp"
#include "Destado.hpp"

using namespace std;

class Automata {
private:
    set<int> estados;
    set<char> alfabeto;
    vector<vector<Transicion>> transiciones;
    int estado_inicial;
    set<int> estados_aceptacion;

public:
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
        for (int i = 0; (unsigned)i < transiciones.size(); i++) {
            for (int j = 0; (unsigned)j < transiciones[i].size(); j++) {
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
        for (int i = 0; (unsigned)i < transiciones.size(); i++) {
            for (int j = 0; (unsigned)j < transiciones[i].size(); j++) {
                archivo << "\t" << i << " -> " << transiciones[i][j].get_estado() << " [label = \"";
                archivo << transiciones[i][j].get_simbolo() << "\"];" << endl;
            }
        }
        archivo << "}";
        archivo << endl;
    }
};

class AFD : public Automata {
public:
    AFD(set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion)
        : Automata(estados, alfabeto, estado_inicial, estados_aceptacion) {
    }

    AFD(set<int> estados, set<char> alfabeto, vector<vector<Transicion>> transiciones,int estado_inicial, set<int> estados_aceptacion) 
        : Automata(estados, alfabeto, transiciones, estado_inicial, estados_aceptacion) {
    }
};

class AFN : public Automata {
public:
    AFN (set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion) 
        :Automata(estados, alfabeto, estado_inicial, estados_aceptacion) {
    }

    AFN(set<int> estados, set<char> alfabeto, vector<vector<Transicion>> transiciones,int estado_inicial, set<int> estados_aceptacion) 
        : Automata(estados, alfabeto, transiciones, estado_inicial, estados_aceptacion) {
    }

    //Convierte un AFN en un AFD
    AFD subconjuntos(void) { 
        set<int> aceptacion;
        vector<vector<Transicion>> d_tran = tabla_transicion(aceptacion);
        set<int> estados;
        for (int i = 0; (unsigned)i < d_tran.size(); i++) {
            estados.insert(i);
        }
        set<char> alfabeto = get_alfabeto();

        AFD resultado = AFD(estados, alfabeto, d_tran, 0, aceptacion);
        return resultado;   
    }

private:
    //Cerradura-épsilon(s) s es un estado
    set<int> cerradura_epsilon(int estado) {
        set<int> conjunto;
        vector<vector<Transicion>> aux_t = get_transiciones();
        vector<bool> visitado(aux_t.size(), false);
        dfs(estado, conjunto, visitado);
        return conjunto;
    }

    //Cerradura-épsilon(T) T es un conjunto
    set<int> cerradura_epsilon(set<int> T) {
        set<int> conjunto;
        for (int elemento : T) {
            set<int> conjunto_auxiliar = cerradura_epsilon(elemento);
            for (int elemento_auxiliar : conjunto_auxiliar) {
                conjunto.insert(elemento_auxiliar);
            }
        }
        return conjunto;
    }

    //Función auxiliar para hacer recorridos en el grafo
    void dfs(int estado, set<int> &conjunto, vector<bool> &visitado) {
        if (visitado[estado]) {
            return;
        }
        visitado[estado] = true;
        conjunto.insert(estado);

        vector<vector<Transicion>> aux_t = get_transiciones();
        for (Transicion destino : aux_t[estado]) {
            if (destino.get_simbolo() == 'E') {
                dfs(destino.get_estado(), conjunto, visitado);
            }
        }
    }

    //Mover(T,a)
    set<int> mover(set<int> T, char simbolo) {
        set<int> conjunto;
        vector<vector<Transicion>> aux_t = get_transiciones();
        for (int elemento : T) {
            for (Transicion destino : aux_t[elemento]) {
                if (destino.get_simbolo() == simbolo) {
                    conjunto.insert(destino.get_estado());
                }
            }
        }
        return conjunto;
    }

    //Función que genera tabla de transición
    vector<vector<Transicion>> tabla_transicion(set<int> &aceptacion) {
        vector<vector<Transicion>> lista_adyacencia;
        vector<Destado> d_estados;
        set<int> aux = cerradura_epsilon(get_estado_inicial());
        d_estados.push_back(Destado(aux, false));
        int actual = primero_sin_marcar(d_estados);

        while (actual != -1) {
            d_estados[actual].set_marcado(true);
            for (char a : get_alfabeto()) {
                set<int> U = cerradura_epsilon(mover(d_estados[actual].get_conjunto(), a));
                if (!esta_en(U, d_estados)) {
                    d_estados.push_back(Destado(U, false));
                }
                int siguiente = idx_conjunto(U, d_estados);
                if (lista_adyacencia.size() < d_estados.size()) {
                    lista_adyacencia.resize(d_estados.size());
                }
                lista_adyacencia[actual].push_back(Transicion(a, siguiente));
                if (es_de_aceptacion(d_estados[actual].get_conjunto())) {
                    aceptacion.insert(actual);
                }
            }
            actual = primero_sin_marcar(d_estados);
        }
       return lista_adyacencia;
    }

    //Función auxiliar de tabla_transicion() que nos regresa el índice de el primer
    //estado sin marcar, si ya están procesados todos los estados regresa -1
    int primero_sin_marcar(vector<Destado> &d_estados) {
        for (int i = 0; (unsigned)i < d_estados.size(); i++) {
            if (d_estados[i].get_marcado() == false) {
                return i;
            }
        }
        //No se encontró ningún estado sin marcar
        return -1;
    }

    //Función auxiliar de tabla_transicion() que nos dice si estado U se encuentra
    //en los estados procesados
    bool esta_en(set<int> &U, vector<Destado> &d_estados) {
        for (Destado d : d_estados) {
            if (d.get_conjunto() == U) {
                return true;
            }
        }
        return false;
    }

    //Función auxiliar de tabla_transicion() que indica el índice del conjunto U en 
    //el vector de d_estados, si no topa al conjunto U regresa -1
    int idx_conjunto(set<int> &U, vector<Destado> &d_estados) {
        for (int i = 0; (unsigned)i < d_estados.size(); i++) {
            if (d_estados[i].get_conjunto() == U) {
                return i;
            }
        }

        return -1;
    }

    //Función auxiliar de tabla_transicion() que nos dice si U es un estado de aceptación o no
    bool es_de_aceptacion(set<int> U) {
        set<int> aceptacion = get_estados_aceptacion();
        for (int u: U) {
            if (aceptacion.count(u) > 0) {
                return true;
            }
        }
        return false;
    }
};
