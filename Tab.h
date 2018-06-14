#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>

using namespace std;

class Tab{

private:

	bool sygnal; //инверсия
	int sytting_state; //нынешнее состояние
	char symbol; //символ, с которым мы работаем
	int next_state; //следующее состояние

public:

	Tab(ifstream &file){ //заполнение таблицы и перевод символов из ascii в нормальный язык(относительно)
		string str;
		getline(file, str, ' ');
		this->sygnal = str[0] - 48;
		this->sytting_state = str[1] - 48;
		this->symbol = str[2];
		this->next_state = str[3] - 48;
	}

	~Tab(){}

	bool Inspection(string str, int temp){ //проверка на все поля данного класса
		if (str == "sygnal") return this->sygnal == (bool)temp;
		if (str == "sytting_state") return this->sytting_state == temp;
		if (str == "symbol") return this->symbol == (char)temp;
		if (str == "next_state") return this->next_state == temp;
	}

	int GotoNextState(){ //переход к следующему состоянию
		return this->next_state;
	}

	bool Not(bool flage){ //метод, проверяющий на наличие инверсии в данном действии
		if (this->sygnal == 0) return !flage;
		else return flage;
	}
};