#pragma once

#include "Lexemes.h"
#include "Tab.h"
#include <vector>
#include "Functions.h"

//10 - ������� ������ � ASCII

void Conversion_to_lexemes(bool &ERR)
{

#define TAB_SIZE 93 //������ ������� ���������

	setlocale(LC_ALL, "");

	ifstream function_words("Function words.txt"); //��������� �����
	ifstream operations("Operations.txt"); //��������
	ifstream dividers("Dividers.txt"); //�����������
	ofstream identifier("Identifier.txt"); //��������������
	ofstream int_const("Integer_Constants.txt"); //�������� ���������
	ofstream char_const("Charecter_Constants.txt"); //��������� ���������

	string str; //������
	char ch; //������� ������
	vector<Lexemes> W, I, O, R, N, C, O1, O2, O3; //���������� ���� ���� ���������� ������� ������ ������ � ����� �������� ��������
												  //O1 - ����� ��������, ������� �� ����� ���������� � ������� ����������, ������� �����
												  //O2 - ����� ��������, ������� ����� ����������(��� ��������� ����� !)
												  //O3 - ����� ��������, ������� ��� �� ��������, � �� ����������� ��� ���������� �������� (� !), ��� ����������� �� ��� ����������� ������� � ������������� ����������, � ��� �������� �� ������ ���� ������ � ������
	Lexemes lex; //�������, ���������� �������� ��� ������ �� �����
				 //���� ��� ���������� ������� ������ �� ������
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

	lex.Set(10); //������� ������
	R.push_back(lex);
	lex.Set(9); //���������
	R.push_back(lex);
	lex.Set(32); //������
	R.push_back(lex);

	while (!dividers.eof()) {
		lex.Set_from_file(dividers);
		R.push_back(lex);
	}
	//������ ���� �� Java Script �� ����� � ������
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

	Tab *tab[TAB_SIZE]; //���������� ������� ��������� � � ����������

	for (short i = 0; i < TAB_SIZE; i++)
		tab[i] = new Tab(tab_f);

	int sytting_state = 0; //������� ���������
	bool res, NEXT, END = false, CONTINUE = true;

	for (int i = 0; (i < jsCode.length()) && CONTINUE && (jsCode[0] != 1);)
	{
		ch = jsCode[i];
		++i;
		NEXT = true;
		if (sytting_state == 0) str.clear(); //���� ��������� 0, �� ������ ���������
		for (short j = 0; (j < TAB_SIZE) && NEXT; j++)
			if (tab[j]->Inspection("sytting_state", sytting_state)) { //���� ������� ��������� ������� � ���������� � �������
				if (tab[j]->Inspection("symbol", 'C')) { //���� ������ �� ������� �����, �� ��������� ������� ������
					res = tab[j]->Not(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '_')) { //���� ������ �������������
					res = tab[j]->Not(ch == '_');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'E')) { //���� �
					res = tab[j]->Not(ch == 'E');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'e')) { //���� �
					res = tab[j]->Not(ch == 'e');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '+')) { //���� +
					res = tab[j]->Not(ch == '+');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '-')) { //���� -
					res = tab[j]->Not(ch == '-');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'N')) { //���� �����
					res = tab[j]->Not(ch >= '0' && ch <= '9');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'R')) { //���� �����������

					for (short z = 0; z < R.size(); z++)
						if (R[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '.')) { //���� .
					res = tab[j]->Not(ch == '.');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 39)) { //���� ��������� �������
					res = tab[j]->Not(ch == 39);
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 34)) { //���� ������� �������
					res = tab[j]->Not(ch == 34);
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '/')) { //���� /
					res = tab[j]->Not(ch == '/');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '=')) { //���� =
					res = tab[j]->Not(ch == '=');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '!')) { //���� !
					res = tab[j]->Not(ch == '!');
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'O')) { //���� ��������
					for (short z = 0; z < O.size(); z++)
						if (O[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'X')) { //���� ����� O1
					for (short z = 0; z < O1.size(); z++)
						if (O1[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'Y')) { ////���� ����� O2
					for (short z = 0; z < O2.size(); z++)
						if (O2[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'Z')) { ////���� ����� O3
					for (short z = 0; z < O3.size(); z++)
						if (O3[z].StrCmp(ch)) {
							res = true;
							break;
						}
						else res = false;
						res = tab[j]->Not(res);
						if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", 'f')) { //���� ������� :)
					res = tab[j]->Not(ch == 1);
					if (res) {
						NEXT = false;
						--i;
						END = true;
					}
				}
				if (tab[j]->Inspection("symbol", 10)) { //������� ������
					res = tab[j]->Not((ch == 10) || (i == jsCode.length()));
					if (res) NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '1')) { //���� ������������� ��������� 1
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_1(I, str, identifier, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '2')) { //���� ������������� ��������� 2
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_2(W, I, str, identifier, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '3')) { //���� ������������� ��������� 3
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_3(N, str, int_const, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '4')) { //���� ������������� ��������� 4
					if (!END) i -= 2;
					str.pop_back();
					Semantic_operation_4(CONTINUE, O, str, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '5')) { //���� ������������� ��������� 5
					if (!END) --i;
					Semantic_operation_5(str, IRoL);
					NEXT = false;
				}
				if (tab[j]->Inspection("symbol", '6')) { //���� ������������� ��������� 6
					if (!END) --i;
					Semantic_operation_6(C, str, char_const, IRoL);
					NEXT = false;
					if (ch == 1) CONTINUE = false;
				}
				if (tab[j]->Inspection("symbol", '7')) { //���� ������������� ��������� 7
					if (!END) --i;
					Semantic_operation_7(CONTINUE, R, str, IRoL);
					NEXT = false;
					if (ch == 1) CONTINUE = false;
				}
				if (res) { //���� �� �������
					str.push_back(ch); //������� � ������ ������� ������
					sytting_state = tab[j]->GotoNextState(); //��������� � ��������� ���������
				}
			}
		if (NEXT) { //���� ������ �������� �� ���� ������� �� ����� ����, ������ ������ ���������� ��� ����� Java Script
			CONTINUE = false;
			ERR = true;
			IRoL << "ERROR "; //��������� ������ � ��������� ���������������
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