#include "Vector.h"
#include <iostream>

Vector::Vector() {
	_nMember = 0;
	_vector = nullptr;
}

Vector::Vector(int nMember, float value) {
	_nMember = nMember;
	_vector = new float[_nMember];

	for (int i = 0; i < _nMember; ++i)
		_vector[i] = value;
}

Vector::Vector(const Vector& otherVector) {
	_nMember = otherVector._nMember;
	_vector = new float[_nMember];

	for (int i = 0; i < _nMember; ++i) 
		_vector[i] = otherVector._vector[i];
}

Vector::~Vector() {
	delete[] _vector;
}

int Vector::size() {
	return _nMember;
}

Vector& Vector::operator = (const Vector& otherVector) {
	if (_vector != nullptr)
		delete[] _vector;

	_nMember = otherVector._nMember;
	_vector = new float[_nMember];

	for (int i = 0; i < _nMember; ++i)
		_vector[i] = otherVector._vector[i];

	return *this;
}

float& Vector::operator [] (int index) {
	return _vector[index];
}

/*
	vector A<x1, x2, x3>, B<y1, y2, y3>
	A + B = <x1 + y1, x2 + y2, x3 + y3>
*/
Vector operator + (const Vector& vector1, const Vector& vector2) {
	if (vector1._nMember != vector2._nMember) {
		std::cout << "Do dai hai vector khong bang nhau!!\n";
		return vector1;
	}

	Vector res(vector1);

	for (int i = 0; i < vector1._nMember; ++i)
		res._vector[i] += vector2._vector[i];

	return res;
}

Vector& Vector::operator += (const Vector& otherVector) {
	if (_nMember != otherVector._nMember) {
		std::cout << "Do dai hai vector khong bang nhau!!!";
		return *this;
	}

	for (int i = 0; i < _nMember; ++i)
		_vector[i] += otherVector._vector[i];

	return *this;
}

/*
	Vector A<x1, x2>
	alpha * A = <alpha * x1, alpha * x2>
*/
Vector operator * (const Vector& vector, float alpha) {
	if (vector._vector == nullptr)
		return vector;

	Vector res(vector);

	for (int i = 0; i < vector._nMember; ++i)
		res._vector[i] *= alpha;

	return res;
}

Vector& Vector::operator *= (float alpha) {
	if (_vector == nullptr)
		return *this;

	for (int i = 0; i < _nMember; ++i)
		_vector[i] *= alpha;

	return *this;
}

std::istream& operator >> (std::istream& in, Vector& vector) {
	std::cout << "Nhap vao so luong phan tu cua vector: ";
	in >> vector._nMember;

	if (vector._nMember > 0) {
		vector._vector = new float[vector._nMember];

		std::cout << "Nhap vao cac phan tu cua vector\n";

		for (int i = 0; i < vector._nMember; ++i) {
			std::cout << "Nhap vao phan tu thu " << i + 1 << ": ";
			in >> vector._vector[i];
		}
	}
	
	return in;
}

std::ostream& operator << (std::ostream& out, const Vector& vector) {

	if (vector._nMember == 0) {
		out << "[]\n";
		return out;
	}

	out << "[";

	for (int i = 0; i < vector._nMember - 1; ++i)
		out << vector._vector[i] << ", ";

	out << vector._vector[vector._nMember - 1] << "]\n";

	return out;
}


