#pragma once

#include "Lexemes.h"
#include "Tab.h"
#include <vector>
#include "Functions.h"

//10 - перевод строки в ASCII

void Conversion_to_lexemes(bool &ERR)
{

#define TAB_SIZE 93 //размер таблицы состояний

	setlocale(LC_ALL, "");

	ifstream function_words("Function words.txt"); //служебные слова
	ifstream operations("Operations.txt"); //операции
	ifstream dividers("Dividers.txt"); //разделители
	ofstream identifier("Identifier.txt"); //идентификаторы
	ofstream int_const("Integer_Constants.txt"); //числовые константы
	ofstream char_const("Charecter_Constants.txt"); //строковые константы

	string str; //буффер
	char ch; //текущий символ
	vector<Lexemes> W, I, O, R, N, C, O1, O2, O3; //объявление всех выше упомянутых классов лексем вместе с тремя классами операций
												  //O1 - класс операций, которые не могут сочетаться с другими операциями, образуя новую
												  //O2 - класс операций, которые могут сочетаться(все отношения кроме !)
												  //O3 - класс операций, который идёт на проверку, в нём перечислены все однотипные операции (и !), они проверяются не при определении лексемы в симантических процедурах, а при переходе из одного типа лексем в другой
	Lexemes lex; //лексема, являющаяся буффером при чтении из файла
				 //ниже идёт заполнение классов лексем из файлов
	while (!function_words.eof()) {
		lex.Set_from_file(function_words);
		W.push_back(lex);
	}

	for (int i = 0; i < 4; i++) {
		lex.Set_from_file(operations);
		O1.push_back(lex);
	}

	for (int i = 0; i < 3; i++) {
		lex.Set_from_file(operations);
		O2.push_back(lex);
	}

	for (int i = 0; i < 9; i++) {
		lex.Set_from_file(operations);
		O3.push_back(lex);
	}

	while (!operations.eof()) {
		lex.Set_from_file(operations);
		O.push_back(lex);
	}

	lex.Set(10); //перенос строки
	R.push_back(lex);
	lex.Set(9); //табуляция
	R.push_back(lex);
	lex.Set(32); //пробел
	R.push_back(lex);

	while (!dividers.eof()) {
		lex.Set_from_file(dividers);
		R.push_back(lex);
	}
	//запись кода на Java Script из файла в строку
	ifstream js_code("JS_code.txt");

	string jsCode;
	while (!js_code.eof()) {
		js_code.get(ch);
		jsCode.push_back(ch);
	}
	jsCode[jsCode.length() - 1] = 1;

	js_code.close();

	ifstream tab_f("Tab.txt");
	ofstream IRoL("internal representation of lexemes.txt");

	Tab *tab[TAB_SIZE]; //объявление таблицы состояний и её заполнение

	for (short i = 0; i < TAB_SIZE; i++)
		tab[i] = new Tab(tab_f);

	int sytting_state = 0; //текущее состояние
	bool res, NEXT, END = false, CONTINUE = true;

	for (int i = 0; (i < jsCode.length()) && CONTINUE && (jsCode[0] != 1);)
	{
		ch = jsCode[i];
		++i;
		NEXT = true;
		if (sytting_state == 0) str.clear(); //если состояние 0, то буффер очищается
		for (short j = 0; (j < TAB_SIZE) && NEXT; j++)
			if (tab[j]->Inspection("sytting_state", sytting_state)) { //если текущее состояние совпало с состоянием в таблице
				if (tab[j]->Inspection("symbol", 'C')) { //если символ из таблицы буква, то проверяем текущий символ
					res = tab[j]->Not(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '_')) { //если нижнее подчёркивание
					res = tab[j]->Not(ch == '_');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'E')) { //если Е
					res = tab[j]->Not(ch == 'E');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'e')) { //если е
					res = tab[j]->Not(ch == 'e');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '+')) { //если +
					res = tab[j]->Not(ch == '+');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '-')) { //если -
					res = tab[j]->Not(ch == '-');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'N')) { //если цифра
					res = tab[j]->Not(ch >= '0' && ch <= '9');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'R')) { //если разделитель

					for (short z = 0; z < R.size(); z++)
						if (R[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '.')) { //если .
					res = tab[j]->Not(ch == '.');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 39)) { //если одинарные ковычки
					res = tab[j]->Not(ch == 39);
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 34)) { //если двойные ковычки
					res = tab[j]->Not(ch == 34);
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '/')) { //если /
					res = tab[j]->Not(ch == '/');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '=')) { //если =
					res = tab[j]->Not(ch == '=');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '!')) { //если !
					res = tab[j]->Not(ch == '!');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'O')) { //если операция
					for (short z = 0; z < O.size(); z++)
						if (O[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'X')) { //если класс O1
					for (short z = 0; z < O1.size(); z++)
						if (O1[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'Y')) { ////если класс O2
					for (short z = 0; z < O2.size(); z++)
						if (O2[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'Z')) { ////если класс O3
					for (short z = 0; z < O3.size(); z++)
						if (O3[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'f')) { //если смайлик :)
					res = tab[j]->Not(ch == 1);
					if (res) {
						NEXT = false;
						--i;
						END = true;
					}
				}
				if (tab[j]->Inspection("symbol", 10)) { //перенос строки
					res = tab[j]->Not((ch == 10) || (i == jsCode.length()));
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '1')) { //если симантическая процедура 1
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_1(I, str, identifier, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '2')) { //если симантическая процедура 2
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_2(W, I, str, identifier, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '3')) { //если симантическая процедура 3
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_3(N, str, int_const, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '4')) { //если симантическая процедура 4
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_4(CONTINUE, O, str, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '5')) { //если симантическая процедура 5
					if (!END) --i;
					Semantic_operation_5(str, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '6')) { //если симантическая процедура 6
					if (!END) --i;
					Semantic_operation_6(C, str, char_const, IRoL);
					NEXT = false;
					if (ch == 1) CONTINUE = false;
				}
				if (tab[j]->Inspection("symbol", '7')) { //если симантическая процедура 7
					if (!END) --i;
					Semantic_operation_7(CONTINUE, R, str, IRoL);
					NEXT = false;
					if (ch == 1) CONTINUE = false;
				}
				if (res) { //если всё совпало
					str.push_back(ch); //заносим в буффер текущий символ
					sytting_state = tab[j]->GotoNextState(); //переходим в следующее состояние
				}
			}
		if (NEXT) { //если символ прошёлся по всей таблице не найдя себя, значит символ недопустим для языка Java Script
			CONTINUE = false;
			ERR = true;
			IRoL << "ERROR "; //выводится ошибка и программа остонавливается
		}
	}
	tab_f.close();
	js_code.close();
	IRoL.close();

	function_words.close();
	operations.close();
	dividers.close();
	identifier.close();
	int_const.close();
	char_const.close();
}