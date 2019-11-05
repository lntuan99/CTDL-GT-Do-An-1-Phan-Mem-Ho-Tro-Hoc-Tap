#pragma once
#include <iostream>
#include <vector>

class Matrix
{
private:
	int _row, _col;
	std::vector<std::vector<double>> _matrix;
	std::vector<std::vector<double>> _inverseMatrix;
	long _determinant;

public:
	//default constructor
	Matrix();

	//paramater constructor
	Matrix(int row, int col, int value);

	//copy constructor
	Matrix(const Matrix& otherMatrix);

	void inverseMatrix();
	void printInverseMatrix();

	long calcDeterminant(std::vector<std::vector<double>> det, int n);
	void printDeterminant();

	//calculate rank of Matrix
	int calcRank();

	//overload operator * 
	friend Matrix operator * (const Matrix&, const Matrix&);

	//overload operator =
	Matrix& operator = (const Matrix&);

	//overload operator >>
	friend std::istream& operator >> (std::istream&, Matrix&);

	//overload operator >>
	friend std::ostream& operator << (std::ostream&, const Matrix&);

	int getRow();
	int getCol();
};

