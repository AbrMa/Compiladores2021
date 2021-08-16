#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Automata {
	public:
		vector <char> sigma; // simbolos de entrada
		vector <int> Q; // conjunto de estados
		int q0; // estado inicial
		vector <int> F; // conjunto estados finales
};

class FinDet { 
	public:
		unordered_map <int, char> f; // función de transición
};

class NoDet { 
	public:
		unordered_map <int, vector <int> > f; // función de transición
};

int main () {
	return 0;
}
