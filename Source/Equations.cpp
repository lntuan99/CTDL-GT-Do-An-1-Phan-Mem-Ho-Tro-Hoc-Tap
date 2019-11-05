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

// Nhập vào hệ phương trình
std::istream& operator >> (std::istream& in, Equations& equa) {
	std::cout << "Nhap vao so phuong trinh: ";
	in >> equa._numEqua;

	std::cout << "Nhap vao so bien cua phuong trinh: ";
	in >> equa._numVarible;

	equa._coefficient = new double* [equa._numEqua];

	for (int i = 0; i < equa._numEqua; ++i)
		equa._coefficient[i] = new double[equa._numVarible];

	equa._sol = new double[equa._numEqua];
	
	std::cout << "\nNhap vao he so cac bien theo thu tu tu X1 .. Xn va ket qua phuong trinh \n\n";
	for (int i = 0; i < equa._numEqua; ++i) {
		std::cout << "Nhap vao he so cua phuong trinh thu " << i + 1 << "\n";

		for (int j = 0; j < equa._numVarible; ++j) {
			std::cout << "He so cua: x" << j + 1 << ": ";
			in >> equa._coefficient[i][j];
		}

		std::cout << "Nhap vao ket qua cua phuong trinh thu " << i + 1 << ": ";
		in >> equa._sol[i];

		std::cout << "\n\n";
	}

	return in;
}

//In ra hệ phương trình vừa nhập
std::ostream& operator << (std::ostream& out, const Equations& equa) {
	for (int i = 0; i < equa._numEqua; ++i) {
		for (int j = 0; j < equa._numVarible; ++j)
			out << equa._coefficient[i][j] << "*x" << j + 1 << "\t";
		out << " = " << equa._sol[i] << "\n";
	}

	return out;
}

//Tính toán kết quả.
void Equations::calcResult() {
	/*
		Tính rank của ma trận kết hợp
	*/
	int rank = _numEqua;
	
	/*
		Biến đổi ma trận các nghiệm về dạng bậc thang
	*/
	for (int cnt = 0; cnt < _numEqua; ++cnt) {
		double k1 = _coefficient[cnt][cnt];

		for (int i = cnt + 1; i < _numEqua; ++i) {
			double k2 = -_coefficient[i][cnt];

			for (int j = cnt; j < _numVarible; ++j)
				_coefficient[i][j] = _coefficient[i][j] * k1 + _coefficient[cnt][j] * k2;
			
			_sol[i] = _sol[i] * k1 + _sol[cnt] * k2;
		}
	}

	/*
		rank của ma trận = số phương trình - số phương trình sau khi biến đổi hoàn toàn bằng 0
	*/
	for (int i = 0; i < _numEqua; ++i) {
		int cnt = 0;

		for (int j = 0; j < _numVarible; ++j)
			if (_coefficient[i][j] == 0)
				++cnt;

		if (cnt == _numVarible)
			--rank;
	}

	/*
		Nếu rank của ma trận bằng 0 => hệ phương trình vô nghiệm
	*/
	if (rank == 0) {
		std::cout << "Khong the giai he phuong trinh";
		return;
	}

	/*
		Nếu rank của ma trận bằng số nghiệm => phương trình có nghiệm duy nhất
	*/
	if (rank == _numVarible) {
		for (int i = _numEqua - 1; i >= 0; --i) {
			double tmp = 0;

			for (int j = i + 1; j < _numVarible; ++j) {
				tmp += (_coefficient[i][j] * _sol[j]);
			}

			_sol[i] = (_sol[i] - tmp) / _coefficient[i][i];
			if (_sol[i] == -0)
				_sol[i] = 0;
		}

		std::cout << "Result: \n";
		for (int i = 0; i < _numVarible; ++i)
			std::cout << "x" << i + 1 << " = " << _sol[i] << "\n";
	}

	/*
		Nếu Rank của ma trận nhỏ hơn số nghiệm của hệ thì hệ có vô số nghiệm
	*/
	else if (rank < _numVarible) {
		/*
			diff là độ chênh lệch giữa số nghiệm của hệ phương trình và rank của hệ
		*/
		int diff = _numVarible - rank;

		/*
			kiểm tra xem có phương trình nào của hệ sau khi biến đổi về ma trận tam giác thì hệ số của tất cả các biến bằng 0 
			nhưng kết quả của phương trình không bằng 0 thì phương trình vô nghiệm
		*/
		for (int i = _numEqua - 1; i >= rank; --i)
			if (_sol[i] != 0) {
				std::cout << "khong the giai he phuong trinh!\n";
				return;
			}

		/*
			Một biến sẽ có 2 phần là hệ số của các ẩn tự do và hệ số tự do
			Ví dụ: x1 = 2a1 + 5
				- a1 là ẩn tự do với hệ số là 2
				- 5 là hệ số tự do

			Đặt các biến là các ẩn tự do. Có số diff nghiệm được đặt là ẩn tự do với hệ số ẩn tự do là 1 và hệ số tự do là 0
		*/
		for (int i = 0; i < diff; ++i) {
			ResultVariable res;
			res.numFree = 0;
			res.result.numCoef[i] = 1;

			_result.push_back(res);
		} 

		/*
			Tính toán các nghiệm còn lại dựa trên các nghiệm đã được bằng ẩn tự do.

			x1 được tính theo x2 .. xn
			x2 được tính theo x3 .. xn
			....
			xn-1 được tính theo xn.
		*/
		for (int i = rank - 1; i >= 0; --i) {
			ResultVariable res;
			res.numFree = _sol[i];

			int cnt = 0;

			for (int j = _numVarible - 1; j > i; --j) {
				res.numFree -= _coefficient[i][j] * _result[cnt].numFree;

				for (int k = 0; k < diff; ++k) 
					res.result.numCoef[k] -= (_coefficient[i][j] * _result[cnt].result.numCoef[k]);
				
				++cnt;
			}

			res.numFree /= _coefficient[i][i];
			for (int j = 0; j < diff; ++j)
				res.result.numCoef[j] /= _coefficient[i][i];

			_result.push_back(res);
		}

		/*
			In kết quả
		*/
		std::cout << "Result: \n";
		for (int i = _numVarible - 1; i >= 0; --i) {
			std::cout << "x" << _numVarible - i << " = ";
			int cnt1 = 0;
			int cnt2 = 0;

			for (int j = 0; j < diff; ++j) {
				
				if (_result[i].result.numCoef[j] != 0) {
					++cnt1;
					++cnt2;

					if (_result[i].result.numCoef[j] == 1 && cnt2 == 1)
						std::cout << "a" << j + 1;
					else if (_result[i].result.numCoef[j] == 1)
						std::cout << " + a" << j + 1;
					else if (_result[i].result.numCoef[j] < 0 && cnt2 == 1)
						std::cout << "-" << -_result[i].result.numCoef[j] << "a" << j + 1;
					else if (_result[i].result.numCoef[j] < 0)
						std::cout << " - " << -_result[i].result.numCoef[j] << "a" << j + 1;
					else if (_result[i].result.numCoef[j] > 0 && cnt2 == 1)
						std::cout << _result[i].result.numCoef[j] << "a" << j + 1;
					else if (_result[i].result.numCoef[j] > 0)
						std::cout << " + " << _result[i].result.numCoef[j] << "a" << j + 1;
				}
			}

			if (cnt1 != 0) {
				if (_result[i].numFree < 0)
					std::cout << " - " << -_result[i].numFree;
				else if (_result[i].numFree > 0)
					std::cout << " + " << _result[i].numFree;
			}

			else
				std::cout << _result[i].numFree;

			std::cout << "\n";
		}

		std::cout << "\nVoi {";

		for (int i = 0; i < diff - 1; ++i)
			std::cout << "a" << i + 1 << ", ";

		std::cout << "a" << diff << "} la cac an so tu do thuoc R";
	}
}



