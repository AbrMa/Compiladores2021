#include <set>
using namespace std;

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