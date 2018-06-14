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

	void Set_from_file(ifstream &f){ //считывание из файла
		getline(f, this->str, (char)10); //считывание строки до переноса
	}

	void Set(char str){ //присваивание символа
		this->str = str;
	}

	string Get(){
		return this->str;
	}

	void Set(string str){ //присваивание строки
		this->str = str;
	}

	bool StrCmp(char ch){ //сравнение символа со строкой(названием лексемы)
		string str;
		str.push_back(ch);
		return this->str == str;
	}
	bool StrCmp(string str){ //сравнение строки со строкой(названием лексемы)
		return this->str == str;
	}
};