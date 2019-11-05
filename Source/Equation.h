#pragma once
#include <string>
#include <vector>

class Equations
{	
private:
	double** _coefficient;
	double* _sol;
	int _numEqua;
	int _numVarible;
	std::string _result;

public:
	Equations();
	~Equations();

	friend std::istream& operator >> (std::istream&, Equations&);
	friend std::ostream& operator << (std::ostream&, const Equations&);
};

