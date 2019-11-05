#pragma once
#include <string>
#include <vector>

class ResultOne
{
public:
	double numCoef[100] = { 0 };
};

class ResultVariable
{
public:
	double numFree;
	ResultOne result;
};

class Equations
{	
private:
	double** _coefficient;
	double* _sol;
	int _numEqua;
	int _numVarible;
	std::vector<ResultVariable> _result;

public:
	Equations();
	~Equations();

	void calcResult();

	friend std::istream& operator >> (std::istream&, Equations&);
	friend std::ostream& operator << (std::ostream&, const Equations&);
};

