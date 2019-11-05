#include "FunctionBool.h"
#include <algorithm>
#include <sstream>
#include <algorithm>

FunctionBool::FunctionBool() {
	_nVariable = 0;
	_nMinterm = 0;
}

//Nhập vào chuỗi hàm cần thu gọn
void FunctionBool::getInput() {
	std::cout << "Nhap vao so luong bien: ";
	cin >> _nVariable;
	
	vector<bool> flag(pow(2, _nVariable));

	std::cout << "Nhap vao ham can thu gon: ";
	rewind(stdin);
	getline(cin, _functionInput); 

	stringstream input(_functionInput);
	string tempString;

	while (getline(input, tempString, ' '))
		_functionInputs.push_back(tempString);
	
	for (auto s : _functionInputs) {
		map<char, int> tempMap;
		for (int i = 'a'; i < 'a' + _nVariable; ++i)
			tempMap[i] = 2;

		for (int i = 0; i < s.size(); ++i) {
			for (int j = 0; j < _nVariable; ++j)
				if (s[i] == 'a' + j)
					if (s[i + 1] == '\'')
						tempMap['a' + j] = 0;
					else
						tempMap['a' + j] = 1;
		}

		vector<bool> check(_nVariable);
		vector<int> tempBin(_nVariable);

		for (int i = 'a'; i < 'a' + _nVariable; ++i) {
			if (tempMap[i] == 0 || tempMap[i] == 1) {
				tempBin[i - 'a'] = tempMap[i];
				check[i - 'a'] = true;
			}
		}

		produceBin(tempBin, check, flag, 0);
	}

	_nMinterm = _binMinTerms.size();
}

//Sinh ra các số nhị phân có thể có
void FunctionBool::produceBin(vector<int> bin, vector<bool> check, vector<bool>& flag, int i) {
	/*
		Sử dụng đệ quy để xây dựng tất cả các số nhị phân có thể có
	*/
	
	/*
		Khi vị trí chèn 1 hoặc 0 đã bằng độ dài chuỗi nhị phân thì đổi nhị phân sang thập phân và đưa vào list minterm
	*/

	/*
		flag dùng để đánh dấu các số đã được thêm vào, tránh thêm lại
	*/
	if (i == _nVariable) {
		int temp = binToInt(bin);

		if (!flag[temp]) {
			flag[temp] = true;
			_intMinTerms.push_back(temp);
			_binMinTerms.push_back(intToBinString(temp));
		}

		return;
	}
	
	/*
		Nếu vị trí đó đã cố định là 1 hoặc 0 thì k xét và đệ quy tới vị trí tiếp theo
	*/
	if (check[i])
		produceBin(bin, check, flag, i + 1);

	else 
		/*
			Chọn 1 hoặc 0 cho vị trí cần xét.
		*/
		for (int k = 0; k <= 1; ++k) {
			bin[i] = k;
			/*
				đệ quy cho các bit kế tiếp
			*/
			produceBin(bin, check, flag, i + 1);
		}
}

//chuyển từ hệ nhị phân sang thập phân
int FunctionBool::binToInt(vector<int> bin) {
	int temp = 0;

	for (int i = 0; i < bin.size(); ++i)
		temp += bin[i] * pow(2, bin.size() - i - 1);

	return temp;
}

//chuyển từ hệ thập phân sang nhị phân dưới dạng chuỗi 
string FunctionBool::intToBinString(int val) {
	string bin;

	bin = bitset<MaxBits>(val).to_string();
	bin = bin.substr(MaxBits - _nVariable);

	return bin;
}

/*
	chuyển từ hệ nhị phân sang dạng biến chữ
	VD: 1011 <=> ab'cd, -1-1 <=> bd
*/
string FunctionBool::binToStringVariable(const string& bin) {
	string res = "";
	int len = bin.length();

	for (int i = 0; i < len; ++i)
		if (bin[i] == '1')
			res += ('a' + i);
		else if (bin[i] == '0') {
			res += ('a' + i);
			res += '\'';
		}
		
	return res;
}

//Đếm số bit 1 trong chuỗi nhị phân
int FunctionBool::getBit1(const string& bin) {
	int len = bin.length();
	int cnt = 0;

	for (int i = 0; i < len; ++i)
		if (bin[i] == '1')
			++cnt;

	return cnt;
}

//So sánh hai chuỗi nhị phân với phân với nhau, chỉ được sai khác nhau ở 1 bit
bool FunctionBool::compareBin(const string& bin1, const string& bin2) {
	int len = bin1.length();
	int cnt = 0;

	for (int i = 0; i < len; ++i)
		if (bin1[i] != bin2[i])
			++cnt;

	if (cnt == 1)
		return true;

	return false;
}

//So sánh các nhân tố kết hợp với các minterm.
bool FunctionBool::compareImpVsMinterm(const string& imp, const string& minterm) {
	for (int i = 0; i < imp.size(); ++i)
		if (imp[i] != '-')
			if (imp[i] != minterm[i])
				return false;

	return true;
}

//Thay thế bit khác nhau thành -
string FunctionBool::replaceDiffBin(string bin1, string bin2) {
	int len = bin1.length();

	for (int i = 0; i < len; ++i)
		if (bin1[i] != bin2[i])
			bin1[i] = '-';

	return bin1;
}

//Đếm số lượng ' để tiện cho việc tìm kết quả cuối cùng 
int FunctionBool::countApos(string s) {
	int cnt = 0;
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == '\'')
			++cnt;

	return cnt;
}

//Tạo ra bảng với các dòng là nhóm các bin có số bit 1 bằng nhau
void FunctionBool::createTable() {
	_table = vector<vector<string>>(_nVariable + 1);

	for (int i = 0; i < _nMinterm; ++i) {
		int num1 = getBit1(_binMinTerms[i]);
		_table[num1].push_back(_binMinTerms[i]);
	}
}

//Kiểm tra bảng có rỗng hay không
bool FunctionBool::isEmptyTable() {
	for (int i = 0; i < _table.size(); ++i)
		if (_table[i].size() != 0)
			return false;

	return true;
}

//Tạo ra bảng mới từ bảng cũ nhờ vào so sánh và kết hợp các bin trong từng nhóm có số bit bằng nhau 
vector<vector<string>> FunctionBool::combineTable(set<string>& impTemp) {
	int size = _table.size();

	//Bảng mới sau khi thực thi sẽ chỉ còn lại n - 1 nhóm với n là số nhóm của bảng cũ.
	vector<vector<string>> newTable(size - 1);

	//Mảng 2 chiều đánh dấu các implicant đã được so sánh và kết hợp
	bool** checked = new bool* [size];

	for (int i = 0; i < size; ++i)
		checked[i] = new bool[_nMinterm];

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < _nMinterm; ++j)
			checked[i][j] = false;

	for (int i = 0; i < size - 1; ++i) //Quét hết các nhóm có trong bảng
		for (int j = 0; j < _table[i].size(); ++j) //Quét các phần tử có trong nhóm thứ i
			for (int k = 0; k < _table[i + 1].size(); ++k) //So sánh với tất cả các phần tử có trong nhóm i + 1
				if (compareBin(_table[i][j], _table[i + 1][k])) {
					checked[i][j] = true;
					checked[i + 1][k] = true;
					newTable[i].push_back(replaceDiffBin(_table[i][j], _table[i + 1][k]));
					//Bảng mới ở nhóm i sẽ push vào implicant đã được so sánh và kết hợp
				}

	//Kiểm tra sau khi quết hết bảng mà implicants nào chưa được đánh dấu thì lưu lại vì nó sẽ chắc chắn có trong kết quả 
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < _table[i].size(); ++j)
			if (!checked[i][j])
				impTemp.insert(_table[i][j]);

	for (int i = 0; i < size; ++i)
		delete[] checked[i];
	delete[] checked;

	return newTable;
}

//Xử lí bảng
void FunctionBool::processTable() {
	createTable();

	set<string> impTemp;
	
	//Thực hiện cho đến khi nào bảng không còn nhóm nào nữa
	while (!isEmptyTable())
		_table = combineTable(impTemp);

	//convert từ cấu trúc set sang vector
	for (auto x : impTemp)
		_impElements.push_back(x);  
}

//Thu gọn 
void FunctionBool::optimize() {
	//Set 2 chiều với mỗi hàng là 1 một vector bool
	set<vector<bool>> mintermTableTemp;

	//So sánh từng minterm với các implicant còn lại để check implicant nào có thể biểu diễn được minterm
	for (int j = 0; j < _nMinterm; ++j) {
		vector<bool> temp;
		for (int i = 0; i < _impElements.size(); ++i)
			temp.push_back(compareImpVsMinterm(_impElements[i], _binMinTerms[j]));

		mintermTableTemp.insert(temp);
	}

	//convert set sang vector
	vector<vector<bool>> mintermTable;
	for (auto x : mintermTableTemp)
		mintermTable.push_back(x);

	//Bảng đếm 1 minterm có bao nhiểu implicant có thể biểu diễn được nó
	vector<vector<int>> countTable;

	for (int j = 0; j < mintermTable.size(); ++j) {
		
		//Lưu lại vị trí của các implicant có thể biểu diễn được minterm thứ j
		vector<int> temp;
		for (int i = 0; i < _impElements.size(); ++i)
			if (mintermTable[j][i])
				temp.push_back(i);

		//push vector vị trí đó vào bảng đếm
		countTable.push_back(temp);
	}

	vector<bool> flag;

	for (int i = 0; i < mintermTable.size(); ++i)
		flag.push_back(true);

	//Kiểm tra minterm nào chỉ có 1 implicant có thể biểu diễn được nó thì thêm implicant đó vào kết quả dưới dạng biến chữ 
	for (int i = 0; i < countTable.size(); ++i)
		if (countTable[i].size() == 1) {

			//Lấy ra vị trí của implicant có thể biểu diễn duy nhất minterm 
			int idx = countTable[i][0];

			//thêm implicant đó vào kết quả
			_functionResult += (binToStringVariable(_impElements[idx]) + " ");

			//Kiểm tra những minterm có thể được biểu diễn từ implicant thì bỏ đánh dấu nguyên cột minterm đó không xét nữa
			for (int j = 0; j < mintermTable.size(); ++j)
				if (mintermTable[j][idx])
					flag[j] = false;
		}

	//Thu kết quả cuối cùng 
	getFunction(mintermTable, flag, 0);
}

//Thu kết quả cuối cùng 
void FunctionBool::getFunction(vector<vector<bool>> mintermTable, vector<bool> flag, int row) {
	//Vì có thể có nhiều kết quả nên sử dụng đệ quy quét hết tất cả các kết quả.

	int cntTrue = 0;

	//Đếm xem còn cột nào chưa bị gạch đi 
	for (auto b : flag)
		if (b)
			++cntTrue;

	//Nếu đã được gạch hết thì đã xét xong => push kết quả vào danh sách kết quả
	if (cntTrue == 0) {
		_listFunctionResult.push_back(_functionResult);
		return;
	}
	
	//i được gán bằng cột chưa xét. nếu i vẫn còn nhỏ hơn size của flag và flag[i] đã được gạch thì cộng i lên 
	int i = row;
	while (i < flag.size() && !flag[i])
		++i;

	//Vòng while dừng khi gặp flag[i] chưa được gạch
	for (int j = 0; j < _impElements.size(); ++j)

		//Nếu implicant thứ j có thể biểu diễn minterm thứ i thì cộng nó vào chuỗi kết quả 
		if (mintermTable[i][j]) {

			//Mục đích trả lại kết quả cũ trước khi đệ quy nên dùng biến len để lưu lại số kí tự cần lấy lại.
			int len = _functionResult.length();

			_functionResult += (binToStringVariable(_impElements[j]) + " ");
				
			vector<int> temp;

			//bỏ đi cột minterm vì đã có implicant nhận biểu diễn. xét xem implicant đó còn có thể biểu diễn được minterm nào chưa có implicant nào nhận biểu diễn không thì bỏ luôn minterm đó
			for (int k = i; k < flag.size(); ++k)
				if (mintermTable[k][j] && flag[k]) {
					flag[k] = false;
					temp.push_back(k);
				}

			//Đệ quy tiếp tục cho những minterm còn lại chưa được xét
			getFunction(mintermTable, flag, i + 1);

			//Trả lại những cột minterm bị đánh dấu để đệ quy tiếp tục 
			for (auto x : temp)
				flag[x] = true;

			//Trả lại kết quả để đệ quy
			_functionResult = _functionResult.substr(0, len);
		}
}

//Hiển thị kết quả.
void FunctionBool::displayResult() {
	int min = _listFunctionResult[0].length() - countApos(_listFunctionResult[0]);

	for (auto s : _listFunctionResult)
		if (s.length() - countApos(s) < min)
			min = s.length();

	cout << "\nResults: \n";
	for (auto s : _listFunctionResult)
		if (s.length() - countApos(s) == min)
			cout << s << "\n";
}