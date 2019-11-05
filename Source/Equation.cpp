#include "Equations.h"
#include <iostream>

Equations::Equations() {
	_coefficient = nullptr;
	_sol = nullptr;
	_numEqua = 0;
	_numVarible = 0;
}

Equations::~Equations() {
	if (_coefficient != nullptr) delete[] _coefficient;
	if (_sol != nullptr) delete[] _sol;
}

std::istream& operator >> (std::istream& in, Equations& equa) {
	std::cout << "Nhap vao so phuong trinh: ";
	in >> equa._numEqua;

	std::cout << "Nhap vao so bien cua phuong trinh: ";
	in >> equa._numVarible;

	equa._coefficient = new double* [equa._numEqua];


	


}

std::ostream& operator << (std::ostream&, const Equation&) {

}

