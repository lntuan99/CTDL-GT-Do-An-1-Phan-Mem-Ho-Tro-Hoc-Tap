#include "GUI.h"
#include <conio.h>

using namespace std;

void GUI::brand() {
	cout << "********************************************************\n";
	cout << "*     DO AN 1 - CTDL & GT - PHAN MEM HO TRO HOC TAP    *\n";
	cout << "*              CLASS      : 18CTT5C                    *\n";
	cout << "*              AUTHOR     : LE NHAT TUAN               *\n";
	cout << "*              STUDENT ID : 18120632                   *\n";
	cout << "*              INSTRUCTOR : MR. NGUYEN THANH AN        *\n";
	cout << "********************************************************\n";
}

void GUI::mainScene() {
	while (1) {
		system("cls");
		brand();
		int choice = -1;

		cout << "\t\t\tMENU\n";

		cout << "\t1: Tim da thuc toi tieu" << endl;
		cout << "\t2: Tinh toan voi vector" << endl;
		cout << "\t3: Tinh toan tren ma tran" << endl;
		cout << "\t4: Giai he phuong trinh" << endl;
		cout << "\t0: Thoat" << endl;

		do {
			cout << "\n\tNhap vao lua chon cua ban: ";
			cin >> choice;
		} while (choice < 0 || choice > 4);

		if (choice != 0) {
			switch (choice) {
			case 1:
				system("cls");
				brand();
				functionBool();
				choice = -1;
				break;

			case 2:
				system("cls");
				brand();
				vector();
				choice = -1;
				break;

			case 3:
				system("cls");
				brand();
				matrix();
				choice = -1;
				break;

			case 4:
				system("cls");
				brand();
				equations();
				choice = -1;
				break;
			}		
		}
		else 
			break;
	}
}

void GUI::functionBool() {
	FunctionBool functionBool;
	functionBool.getInput();
	functionBool.processTable();
	functionBool.optimize();
	functionBool.displayResult();

	cout << "\nNhan Enter de tiep tuc!!";
	while (_getch() != 13);
}

void GUI::vector() {
	while (1) {
		cout << "\t1: Cong hai vector" << endl;
		cout << "\t2: Nhan vector voi mot so" << endl;
		cout << "\t0: Thoat";

		int choice = -1;
		do {
			cout << "\n\tNhap vao lua chon cua ban: ";
			cin >> choice;
		} while (choice < 0 || choice > 2);

		if (choice != 0) {
			switch (choice) {
			case 1: {
				Vector v1, v2;

				cout << "\nNhap vao vector thu nhat" << endl;
				cin >> v1;

				cout << "\nNhap vao vector thu hai" << endl;
				cin >> v2;

				cout << "Hai vector vua nhap vao" << endl;

				cout << "vector1 : " << v1 << "vector2 : " << v2;
				Vector res = v1 + v2;

				if (v1.size() != v2.size()) {
					cout << "Khong co ket qua!!\n";
					while (_getch() != 13);
					break;
				}

				cout << "vector1 + vector2 = " << res;

				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);

				break;
			}

			case 2: {
				Vector v1;
				float alpha;

				cout << "\nNhap vao vector" << endl;
				cin >> v1;

				cout << "Nhap vao so alpha: ";
				cin >> alpha;

				cout << "vector vua nhap vao" << endl;

				cout << "vector : " << v1;
				Vector res = v1 * alpha;

				cout << "vector * " << alpha << " = " << res;

				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);

				break;
			}
			}

			system("cls");
			brand();
		}
		else
			break;
	}
	
	
}

void GUI::matrix() {

	Matrix matrix1;

	cin >> matrix1;

	cout << "Ma tran vua nhap: " << endl << matrix1;

	cout << "\nNhan Enter de tiep tuc!!";
	while (_getch() != 13);

	while (1) {
		int choice = -1;
		do {
			system("cls");
			brand();
			cout << "\t1: Tim dinh thuc cua ma tran" << endl;
			cout << "\t2: Nghich dao ma tran" << endl;
			cout << "\t3: Tinh tich hai ma tran" << endl;
			cout << "\t4: Tim hang cua ma tran" << endl;
			cout << "\t5: Xem lai ma tran vua nhap" << endl;
			cout << "\t0: Thoat" << endl;
			cout << "\n\tNhap vao lua chon cua ban: ";
			cin >> choice;
		} while (choice < 0 || choice > 5);

		if (choice != 0) {
			switch (choice) {
			case 1: {
				matrix1.printDeterminant();
				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);
				break;
			}

			case 2: {
				matrix1.inverseMatrix();
				matrix1.printInverseMatrix();
				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);
				break;
			}
			case 3: {
				Matrix matrix2;
				cout << "Nhap vao ma tran thu hai" << endl;

				cin >> matrix2;

				Matrix res = matrix1 * matrix2;

				if (matrix1.getCol() != matrix2.getRow()) {
					cout << "Khong co ket qua";
					break;
				}
				cout << "\nResult:\n";
				cout << res;
				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);
				break;
			}
			case 4: {
				int rank = matrix1.calcRank();
				cout << "Hang cua ma tran: " << rank << endl;
				cout << "\nNhan Enter de tiep tuc!!";
				while (_getch() != 13);
				break;
			}
			case 5: {
				cout << "Ma tran vua nhap: " << endl << matrix1 << endl;
				cout << "Nhan Enter de tiep tuc!!!";
				while (_getch() != 13);
				break;
			}
			}
		}
		else
			break;
	}
}

void GUI::equations() {
	Equations equations;

	cin >> equations;
	cout << "He phuong trinh vua nhap: \n";
	cout << equations;

	equations.calcResult();

	cout << "\nNhan Enter de tiep tuc!!";
	while (_getch() != 13);
}

