class Transicion {
    char simbolo;
    int estado;

public:
    Transicion(char simbolo, int estado) {
        this->simbolo = simbolo;
        this->estado = estado;
    }

    char get_simbolo(void) {
        return simbolo;
    }

    int get_estado(void) {
        return estado;
    }
};
