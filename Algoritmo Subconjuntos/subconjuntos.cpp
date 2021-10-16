/*
    Descripción : 
        La construcción de subconjuntos de un AFD, a partir de un Automata.

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
        this->simbolo = simbolo;
        this->estado = estado;
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
        this->conjunto = conjunto;
        this->marcado = marcado;
    }

    //Métodos
    void set_conjunto(set<int> conjunto) {
        this->conjunto = conjunto;
    }

    void set_marcado(bool marcado) {
        this->marcado = marcado;
    }

    set<int> get_conjunto(void) {
        return conjunto;
    }

    bool get_marcado(void) {
        return marcado;
    }
};

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
        for (int i = 0; i < transiciones.size(); i++)
        {
            cout << "Estando en " << i << " puedo ir a :" << endl;
            for (int j = 0; j < transiciones[i].size(); j++)
            {
                cout << "\t" << transiciones[i][j].get_estado() << " con '";
                cout << transiciones[i][j].get_simbolo() << "'" << endl;
            }
        }
    }
};

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

class AFN : public Automata {
public:
    //Constructor
    AFN (set<int> estados, set<char> alfabeto, int estado_inicial, set<int> estados_aceptacion) 
        :Automata(estados, alfabeto, estado_inicial, estados_aceptacion) {
    }

    AFN(set<int> estados, set<char> alfabeto, vector<vector<Transicion>> transiciones,int estado_inicial, set<int> estados_aceptacion) 
        : Automata(estados, alfabeto, transiciones, estado_inicial, estados_aceptacion) {
    }

    //Métodos
    //Convierte un AFN en un AFD
    AFD subconjuntos(void) { 
        set<int> aceptacion;
        vector<vector<Transicion>> d_tran = tabla_transicion(aceptacion);
        set<int> estados;
        for (int i = 0; i < d_tran.size(); i++) {
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
        //Caso base
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
            //cout << "El actual está en la pos " << actual << " : "; 
            //imprime_conjunto(d_estados[actual].get_conjunto());
            d_estados[actual].set_marcado(true);
            for (char a : get_alfabeto()) {
                //cout << "\tcuando proceso '" << a << "' me lleva a";
                //set<int> mov = mover(d_estados[actual].get_conjunto(), a);
                //imprime_conjunto(mov);
                set<int> U = cerradura_epsilon(mover(d_estados[actual].get_conjunto(), a));
                //cout << "ya el vergas debe ser " ;
                //imprime_conjunto(U);
                if (!esta_en(U, d_estados)) {
                    d_estados.push_back(Destado(U, false));
                }

                //armar tabla
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

        /*
        cout << "digraph finite_state_machine { \n";
        cout << "\trankdir = LR;\n\tnode [shape = circle];\n";
        for(int i = 0; i < lista_adyacencia.size(); i++) {
            for (int j = 0; j < lista_adyacencia[i].size(); j++) {
                cout << "\t" <<  i << " -> ";
                cout << lista_adyacencia[i][j].get_estado() << " [label = \"" <<lista_adyacencia[i][j].get_simbolo() <<"\"];" <<  endl;
            }
        }
        cout << "}";
        cout << endl;
        */

       return lista_adyacencia;
    }

    //Función auxiliar de tabla_transicion() que nos regresa el índice de el primer
    //estado sin marcar, si ya están procesados todos los estados regresa -1
    int primero_sin_marcar(vector<Destado> &d_estados) {
        for (int i = 0; i < d_estados.size(); i++) {
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
        for (int i = 0; i < d_estados.size(); i++) {
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
    //ELIMINAR
    void imprime_conjunto(set<int> conjunto) {
    cout << "{";
    for (int elemento : conjunto) {
        cout << elemento << " ";
    }
    cout << "}" <<endl;
    }
};

int main() {
    //AFN 'N' para (a|b)*abb
    set<int> estados = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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
    //set<int> T = N.cerradura_epsilon(6);
    //set<int> T = N.cerradura_epsilon({5});
    //set<int> mover = N.mover({0,1,2,4,7},'b');
    //set<int> mover = N.mover({1,2,4,5,6,7},'b');
    /*
    for (auto r : mover) {
        cout << r << " ";
    }
    cout << endl;
    */
    //N.subconjuntos();
    return 0;
}