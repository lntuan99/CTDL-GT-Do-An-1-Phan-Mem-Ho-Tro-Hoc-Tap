#include "Matrix.h"
#include <algorithm>
#include <iomanip>

Matrix::Matrix() {
	_row = 0;
	_col = 0;
}

Matrix::Matrix(int row, int col, int value) {
	_row = row;
	_col = col;

	for (int i = 0; i < row; ++i) {
		std::vector<double> tmp;

		for (int j = 0; j < col; ++j)
			tmp.push_back(value);

		_matrix.push_back(tmp);
	}
		
}

Matrix::Matrix(const Matrix& otherMatrix) {
	_row = otherMatrix._row;
	_col = otherMatrix._col;

	for (int i = 0; i < _row; ++i) {
		std::vector<double> tmp;

		for (int j = 0; j < _col; ++j)
			tmp.push_back(otherMatrix._matrix[i][j]);

		_matrix.push_back(tmp);
	}
}

int Matrix::getRow() {
	return _row;
}

int Matrix::getCol() {
	return _col;
}

void Matrix::inverseMatrix() {
	if (_row != _col)
		return;

	long long det = this->calcDeterminant(_matrix, _row);

	if (det == 0) {
		std::cout << "Khong the tim ma tran nghich dao!\n";
		return;
	}

	for (int i = 0; i < _row; ++i) {
		std::vector<double> inverse;
		
		//Tạo ra ma trận bỏ đi dòng i cột j
		for (int j = 0; j < _row; ++j) {
			std::vector<std::vector<double>> tmp1;
			double x;

			for (int ii = 0; ii < _row; ++ii) {
			
				if (ii == i)
					continue;
				else {
					std::vector<double> tmp2;

					for (int jj = 0; jj < _row; ++jj)
						if (jj == j)
							continue;
						else
 							tmp2.push_back(_matrix[ii][jj]);

					tmp1.push_back(tmp2);
				}
			}

			x = (std::pow(-1, i + 1 + j + 1) * calcDeterminant(tmp1, _row - 1)) / det;

			if (x == 0)
				inverse.push_back(0);
			else
				inverse.push_back(x);

		}

		_inverseMatrix.push_back(inverse);
	}
}

void Matrix::printInverseMatrix() {
	if (_row != _col) {
		std::cout << "Khong the tim ma tran nghich dao!!!\n";
		return;
	}

	for (int i = 0; i < _row; ++i) {
		for (int j = 0; j < _row; ++j) {
			std::cout.precision(6);
			std::cout << _inverseMatrix[j][i] << std::setw(15);

		}
			
		std::cout << "\n";
	}

	std::cout << "\n";
}

/*
	A = { a }
	det(A) = a 

	A = { a11, a12
		  a21, a22 }
	det(A) = a11 * a22 - a21 * a12 

	A = { a11, a12, a13
		  a21, a22, a23
		  a31, a32, a33 }
	det(A) = (-1)^(1+1) * a11 * det(A11) + (-1)^(1+2) * a12 * det(A12) + (-1)^(1+3) * a13 * det(A13)

	A11 = { a22, a23		A12 = { a21, a23		A13 = { a21, a22 
			a32, a33 }				a31, a33 }				a31, a32 }

	A = { a11, a12, ..., a1n
		  a21, a22, ..., a2n
		  ...
		  an1, an2, ..., ann }
	det(A) = (-1)^(1+1) * a11 * det(A11) + (-1)^(1+2) * a12 * det(A12) + ... + (-1)^(1+n) * a1n * det(A1n)
*/

long Matrix::calcDeterminant(std::vector<std::vector<double>> det, int n) {
	if (n == 1)
		return _matrix[0][0];

	if (n == 2)
		return ((det[0][0] * det[1][1]) - (det[0][1] * det[1][0]));

	long sum = 0;

	for (int cnt = 0; cnt < n; ++cnt) {
		std::vector<std::vector<double>> tmp;
		
		for (int i = 1; i < n; ++i) {
			std::vector<double> tmp1; 

			for (int j = 0; j < n; ++j)
				if (j == cnt)
					continue;
				else
					tmp1.push_back(det[i][j]);

			tmp.push_back(tmp1);
		}

		sum += (pow(-1, cnt) * det[0][cnt] * calcDeterminant(tmp, n - 1));
	}

	return sum;
}

void Matrix::printDeterminant() {
	if (_row != _col) {
		std::cout << "Khong the tinh dinh thuc ma tran khong phai ma tran vuong!!";
		return;
	}

	long det = calcDeterminant(_matrix, _row);

	std::cout << "det = " << det << std::endl;
}

Matrix operator * (const Matrix& matrix1, const Matrix& matrix2) {
	if (matrix1._col != matrix2._row) {
		std::cout << "Khong the thuc hien phep nhan hai ma tran nay voi nhau!!\n";
		return matrix1;
	}
		

	Matrix res;
	
	res._row = matrix1._row;
	res._col = matrix2._col;

	for (int i = 0; i < res._row; ++i) {
		std::vector<double> tmp;

		for (int j = 0; j < res._col; ++j) {
			int sum = 0;

			for (int p = 0; p < matrix1._col; ++p)
				sum += (matrix1._matrix[i][p] * matrix2._matrix[p][j]);

			tmp.push_back(sum);
		}

		res._matrix.push_back(tmp);
	}
		
	return res;
}

Matrix& Matrix::operator = (const Matrix& otherMatrix) {
	_row = otherMatrix._row;
	_col = otherMatrix._col;

	for (int i = 0; i < _row; ++i) {
		std::vector<double> tmp;

		for (int j = 0; j < _col; ++j)
			tmp.push_back(otherMatrix._matrix[i][j]);

		_matrix.push_back(tmp);
	}

	return *this;
}

std::istream& operator >> (std::istream& in, Matrix& matrix) {
	do {
		std::cout << "Nhap vao so hang cua ma tran > 0: ";
		in >> matrix._row;
	} while (matrix._row <= 0);

	do {
		std::cout << "Nhap vao so cot cua ma tran > 0: ";
		in >> matrix._col;
	} while (matrix._col <= 0);
	
	for (int i = 0; i < matrix._row; ++i) {

		std::vector<double> tmp;

		for (int j = 0; j < matrix._col; ++j) {
			int x;

			std::cout << "Nhap vao gia tri phan tu thu " << "[" << i + 1 << ", " << j + 1 << "] = ";

			in >> x;
			
			tmp.push_back(x);
		}

		matrix._matrix.push_back(tmp);
	}

	return in;
}

std::ostream& operator << (std::ostream& out, const Matrix& matrix) {
	for (int i = 0; i < matrix._row; ++i) {
		for (int j = 0; j < matrix._col; ++j)
			out << matrix._matrix[i][j] << std::setw(5);

		out << "\n";
	}

	out << "\n";
		
	return out;
}

int Matrix::calcRank() {
	std::vector<std::vector<double>> tmp(_matrix);
	int rank = _row;
	int min = rank;

	for (int cnt = 0; cnt < min; ++cnt) {
		double k1;
		if (cnt < _col)
			k1 = tmp[cnt][cnt];
		else
			break;

		for (int i = cnt + 1; i < _row; ++i) {
			double k2 = -tmp[i][cnt];
	
			for (int j = cnt; j < _col; ++j)
				tmp[i][j] = (tmp[i][j] * k1 + tmp[cnt][j] * k2);
		}
	}

	for (int i = 0; i < _row; ++i) {
		int cnt = 0;

		for (int j = 0; j < _col; ++j)
			if (tmp[i][j] == 0)
				++cnt;

		if (cnt == _col)
			--rank;
	}
	
	return rank;
}