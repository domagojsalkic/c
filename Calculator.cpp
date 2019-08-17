#include <iostream>
#include <iomanip>
#include <string>

class calcError {
public:
	virtual std::string show_error() = 0;
};

class divideByZero : public calcError {
public:
	std::string show_error() {
		return "divide by zero";
	}
};

class notANumber : public calcError {
public:
	std::string show_error() {
		return "not a number";
	}
};
class invalidOperation : public calcError {
public:
	std::string show_error() {
		return "invalid operation";
	}
};

int unos_broja() {
	int br;
	std::cin >> br;
	if (std::cin.fail())
		throw notANumber();
	return br;
}

char unos_operacije() {
	char c;
	std::cin >> c;
	if (c != '*' && c != '/' && c != '+' && c != '-')
		throw invalidOperation();
	return c;
}

double result(int a, char c, int b) {
	if (c == '*')
		return a * b;
	else if (c == '/') {
		if (b == 0)
			throw divideByZero();
		return static_cast<double>(a) / b;
	}
	else if (c == '+')
		return a + b;
	else if (c == '-')
		return a - b;
}

int main() {
	while (true) {
		try {
			int a = unos_broja();
			char z = unos_operacije();
			int b = unos_broja();
			std::cout << a << z << b << "=" << result(a, z, b) << std::endl;
		}
		catch (calcError& err) {
			std::cout << err.show_error() << std::endl;
			break;
		}
	}
}