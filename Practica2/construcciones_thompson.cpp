#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

//Operadores y su precedencia
const std::unordered_map <char, int> OPERADORES ({{'(', 4}, {')', 4}, {'*', 3}, {'.', 2}, {'|', 1}});

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

			/*
			 (a*E)ab(ca|c*d)
			   ij
			 (a

    		         (a*E).a.b.(c.a|c*.d)

			 */
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

		void get_subexpresiones () {
			std::string expresion_completa = agregar_concatenacion();
			std::cout << expresion_completa << std::endl;

			std::stack<char> operandos;

			for (char c : expresion) {
				// Si c es una letra mínuscula debe ser un operando
				if (islower(c) || c == 'E') {
					operandos.push(c);							
				}
				else {
					//operadores.push(c);				
				}

			}
			/*
			while (!operandos.empty()) {
				std::cout << operandos.top() << std::endl;
				operandos.pop();
			}
			while (!operadores.empty()) {
				std::cout << operadores.top() << std::endl;
				operadores.pop();
			}
			*/
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
