#pragma once

#include <iostream>
#include "Lexemes.h"
#include "Tab.h"

using namespace std;

bool Semantic_operation(vector<Lexemes> &lex, string &str, short &num){
	for (short i = 0; i < lex.size(); i++) 
	if (lex[i].StrCmp(str)) { 
		num = i + 1;
		return true;
	}
	num = lex.size() + 1;
	return false;
}

void Semantic_operation_1(vector<Lexemes> &lex, string &str, ofstream &file, ofstream &res){
	Lexemes l;
	short num = 0;
	if (!Semantic_operation(lex, str, num)){
		l.Set(str);
		lex.push_back(l);
		file << str << endl;
		res << 'I' << num << ' ';
	}
	else res << 'I' << num << ' ';
}

void Semantic_operation_2(vector<Lexemes> &lex, vector<Lexemes> &lex2, string &str, ofstream &file, ofstream &res){
	Lexemes l;
	short num = 0;
	if (!Semantic_operation(lex, str, num)){
		if (!Semantic_operation(lex2, str, num)){
			l.Set(str); 
			lex2.push_back(l);
			file << str << endl;
			res << 'I' << num << ' ';
		}
		else res << 'I' << num << ' ';
	}
	else res << 'W' << num << ' ';
}

void Semantic_operation_3(vector<Lexemes> &lex, string &str, ofstream &file, ofstream &res){
	Lexemes l;
	short num = 0;
	if (!Semantic_operation(lex, str, num)){
		l.Set(str);
		lex.push_back(l);
		file << str << endl;
		res << 'N' << num << ' ';
	}
	else res << 'N' << num << ' ';
}

void Semantic_operation_4(bool &cont, vector<Lexemes> &lex, string &str, ofstream &res){
	Lexemes l;
	short num = 0;
	if (Semantic_operation(lex, str, num)) res << 'O' << num << ' ';
	else { 
		res << "ERROR";
		cont = false;
	}
}

void Semantic_operation_5(string &str, ofstream &res){
	str.clear();
	res << endl;
}

void Semantic_operation_6(vector<Lexemes> &lex, string &str, ofstream &file, ofstream &res){
	Lexemes l;
	short num = 0;
	if (!Semantic_operation(lex, str, num)){
		l.Set(str);
		lex.push_back(l);
		file << str << endl;
		res << 'C' << num << ' ';
	}
	else res << 'C' << num << ' ';
}

void Semantic_operation_7(bool &cont, vector<Lexemes> &lex, string &str, ofstream &res){
	Lexemes l;
	short num = 0;
	if (Semantic_operation(lex, str, num))
	{
		if (str[0] != 10 && str[0] != 32 && str[0] != 9) res << 'R' << num << ' ';

		else if (str[0] != 32 && str[0] != 9) res << endl << ' ';
	}
	else { 
		res << "ERROR"; 
		cont = false;
	}
	
}