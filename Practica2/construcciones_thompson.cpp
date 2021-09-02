#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class ExpresionRegular {
	private:
		std::string expresion;

		bool es_operando (char c) {
			if (islower(c) || c == 'E') {
				return true;
			}

			return false;
		}
		
		//agrega de manera explicíta la concatenacion '.' a la cadena 
		//ej. 	ab -> a.b
		std::string agregar_concatenacion () {
			if (expresion.size() <= 1) {
				return expresion;
			}

			std::string expresion_con_concatenacion = "";
			expresion_con_concatenacion += expresion[0];

			for (int i = 0; i < int(expresion.size()) - 1; i++) {
				//ej.	 a(
				bool cond1 = es_operando(expresion[i]) && (expresion[i + 1] == '(');
				//ej.	(a
				bool cond2 = (expresion[i] == ')') && es_operando(expresion[i + 1]);
				//ej.	*a
				bool cond3 = (expresion[i] == '*') && es_operando(expresion[i + 1]); 
				//ej.	ab
				bool cond4 = es_operando(expresion[i]) && es_operando(expresion[i + 1]);

				if (cond1 || cond2 || cond3 || cond4) {
					expresion_con_concatenacion += ".";
				}

				expresion_con_concatenacion += expresion[i + 1];

			}

			return expresion_con_concatenacion;
		}

	public:
		ExpresionRegular (std::string expresion) {
			this -> expresion = expresion;
		}
		
		std::string get_expresion () {
			return expresion;
		}

		void ps (std::stack <char> s) {
			std::cout << "Pila -> ";
			while (!s.empty()) {
				std::cout << s.top() << " ";
				s.pop();
			}
			std::cout << std::endl;
		}

		void get_subexpresiones () {
			std::unordered_map <char, int> precedencia ({{'*', 3}, {'.', 2}, {'|', 1}});
			std::string expresion_completa = agregar_concatenacion();
			std::string orden_postfijo = "";
			std::stack<char> operadores;

//			std::cout << "la expresion completa es " << expresion_completa << std::endl;
			for (char c : expresion_completa) {
				//std::cout << "***************\n";
				//std::cout << "Procesando " << c << std::endl;
				if (es_operando(c)) {
					orden_postfijo += c;
				}
				else { // es operador
					if (operadores.empty()) {
						operadores.push(c);
					}
					else {
						if (c == ')') {
							while (operadores.top() != '(') {
								orden_postfijo += operadores.top();
								operadores.pop();
							}
							operadores.pop();
						}
						else if (operadores.top() == '(') {
							operadores.push(c);
						}
						else if (precedencia[operadores.top()] >= precedencia[c]) {
							orden_postfijo += operadores.top();
							operadores.pop();
							operadores.push(c);	
						}	
						else {
							operadores.push(c);
						}
					}

				}
//				std::cout << "cadena post -> " << orden_postfijo << std::endl;
				//ps(operadores);
			}

			std::cout << orden_postfijo << std:: endl;
		}
};

int main () {
	std::string archivo_txt;
	std::cin >> archivo_txt;
	ExpresionRegular r(archivo_txt);

	std::cout << r.get_expresion() << std::endl;
	r.get_subexpresiones();

	return 0;
}
