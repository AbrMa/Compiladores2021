/*
    Descripción : 
        La construcción de subconjuntos de un AFD, a partir de un Automata.

    Entrada:
        Un AFN 'N'.

    Salida:
        Un AFD 'D' que acepta el mismo lenguaje que N.    
*/
#include <bits/stdc++.h>
#include "AFD.hpp"
#include "AFN.hpp"

using namespace std;

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
    N.imprime_transiciones();
    AFD D = N.subconjuntos();
    D.imprime_transiciones(); 

    //Archivos
    ofstream entrada("entrada.dot");
    N.escribe_archivo(entrada);
    entrada.close();

    ofstream salida("salida.dot");
    D.escribe_archivo(salida);
    salida.close();

    //AFN 'N2' (ab)*|a*c
    /*
    set<int> estados2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    set<char> alfabeto2 = {'a', 'b', 'c'};
    set<int> estados_aceptacion2 = {11};
    AFN N2 = AFN(estados2, alfabeto2, 0, estados_aceptacion2);
    N2.inserta_transicion(0, 'E', 1);
    N2.inserta_transicion(0, 'E', 6);
    N2.inserta_transicion(1, 'E', 2);
    N2.inserta_transicion(1, 'E', 5);
    N2.inserta_transicion(2, 'a', 3);
    N2.inserta_transicion(3, 'b', 4);
    N2.inserta_transicion(4, 'E', 2);
    N2.inserta_transicion(4, 'E', 5);
    N2.inserta_transicion(5, 'E', 11);
    N2.inserta_transicion(6, 'E', 7);
    N2.inserta_transicion(6, 'E', 9);
    N2.inserta_transicion(7, 'a', 8);
    N2.inserta_transicion(8, 'E', 7);
    N2.inserta_transicion(8, 'E', 9);
    N2.inserta_transicion(9, 'c', 10);
    N2.inserta_transicion(10, 'E', 11);
    AFD D2 = N2.subconjuntos(); 

    N2.imprime_transiciones();
    D2.imprime_transiciones();

    //Archivos
    ofstream entrada("entrada.dot");
    N2.escribe_archivo(entrada);
    entrada.close();

    ofstream salida("salida.dot");
    D2.escribe_archivo(salida);
    salida.close();
    */
    return 0;
}