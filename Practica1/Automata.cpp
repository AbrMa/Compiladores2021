#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class AFD {
	public:
		vector <char> sigma; // simbolos de entrada
		vector <int> Q; // conjunto de estados
		int q0; // estado inicial
		vector <int> F; // conjunto estados finales
		unordered_map <int, char> f // función de transición
};

int main () {
	return 0;
}
