/*
	Sử dụng phương pháp Quine-McCluskey để tìm đa thức tối tiểu của hàm bool
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <set>
#include <map>

#define MaxBits 100

using namespace std;

class FunctionBool
{
private:
	string _functionInput;
	vector<string> _functionInputs;
	vector<int> _intMinTerms;
	vector<string> _binMinTerms;
	int _nVariable;
	int _nMinterm;
	vector<vector<string>> _table;
	vector<string> _impElements;
	string _functionResult;
	vector<string> _listFunctionResult;

public: 
	FunctionBool();

	//Đọc vào đa thức cần rút gọn
	void getInput();

	//Đổi hệ nhị phân sang thập phân
	int binToInt(vector<int>);

	//Sinh ra các số nhị phân có thể có
	void produceBin(vector<int>, vector<bool>, vector<bool>&, int);

	//Đổi hệ thập phân sang nhị phân lưu dưới dạng String
	string intToBinString(int);

	//Từ nhị phân đổi sang chuỗi các biến kết quả
	string binToStringVariable(const string&);

	//Đếm số bit = 1 trong chuỗi nhị phân
	int getBit1(const string&);

	//So sánh 2 chuỗi nhị phân
	bool compareBin(const string&, const string&);

	//Thay thế các bit khác nhau thành - 
	string replaceDiffBin(string, string);

	//So sánh các implicant với các minterm
	bool compareImpVsMinterm(const string&, const string&);

	//Tạo bảng nhóm các minterm với số bit 1 tương ứng 
	void createTable();

	//Kiểm tra bảng đã rỗng hay chưa
	bool isEmptyTable();

	//Tạo ra bảng sau khi so sánh các nhóm với nhau
	vector<vector<string>> combineTable(set<string>&);

	//Hoàn thiện bảng 
	void processTable();

	//Thu gọn kết quả
	void optimize();

	//Đếm số dấu '
	int countApos(string s);

	//Thu lại kết quả dưới dạng các biến chữ 
	void getFunction(vector<vector<bool>>, vector<bool>, int);

	//Hiển thị kết quả
	void displayResult();
};

