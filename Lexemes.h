#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Lexemes
{
private:
	string str;

public:
	Lexemes(){}
	~Lexemes(){}

	void Set_from_file(ifstream &f){ //���������� �� �����
		getline(f, this->str, (char)10); //���������� ������ �� ��������
	}

	void Set(char str){ //������������ �������
		this->str = str;
	}

	string Get(){
		return this->str;
	}

	void Set(string str){ //������������ ������
		this->str = str;
	}

	bool StrCmp(char ch){ //��������� ������� �� �������(��������� �������)
		string str;
		str.push_back(ch);
		return this->str == str;
	}
	bool StrCmp(string str){ //��������� ������ �� �������(��������� �������)
		return this->str == str;
	}
};