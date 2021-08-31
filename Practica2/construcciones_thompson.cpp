#include <iostream>
#include <string>

class ExpresionRegular {
	std::string expresion;
	public:
		ExpresionRegular (std::string expresion) {
			this -> expresion = expresion;
		}
		
		std::string get_expresion () {
			return expresion;
		}

};

int main () {
	/*
	std::string regex;
	std::cin >> regex;
	std::cout << regex << std::endl;
	*/
	return 0;
}
