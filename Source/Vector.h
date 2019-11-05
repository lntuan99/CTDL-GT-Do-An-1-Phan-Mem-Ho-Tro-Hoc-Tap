#pragma once
#include <iostream>

class Vector
{
private: 
	float* _vector;
	int _nMember;

public:
	//Default Constructor
	Vector();

	//Paramater Constructor
	Vector(int, float); 

	//Copy Constructor
	Vector(const Vector&);

	//Destructor
	~Vector();

	//overload operator +
	friend Vector operator + (const Vector&, const Vector&);

	//overload operator +=
	Vector& operator += (const Vector&);

	//overload operator *
	friend Vector operator * (const Vector& ,float);

	//overload operator *=
	Vector& operator *= (float);

	//overload operator =
	Vector& operator = (const Vector&);

	//overload operator []
	float& operator [] (int);

	//overload operator >>
	friend std::istream& operator >> (std::istream&, Vector&);

	//overload operator <<
	friend std::ostream& operator << (std::ostream&, const Vector&);

	int size();
};
