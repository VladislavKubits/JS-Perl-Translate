#pragma once

#include <iostream>
#include <string>
#include "Lexemes.h"

using namespace std;

int step(int a, int b){
	int page = 1;
	for (int i = 0; i < b; i++) page *= a;
	return page;
}

class Convert{
public:
	static int toInt(string &str){
		int  page = 0;
		for (int i = 0; i < str.length(); i++) page += (int)(str[i] - 48) *step(10, str.length() - i - 1);
		return page;
	}
	/*static double toDouble(string &str){

	}*/
	static string toFunction_words(string &str, vector<Lexemes> &W){
		for (short j = 0; j < str.length() - 1; j++) str[j] = str[j + 1];
		str.pop_back();
		int page = toInt(str);
		for (int j = 0; j < W.size(); j++){
			if (page - 1 == j){
				if (W[j].StrCmp("return") || W[j].StrCmp("goto")) return W[j].Get();
			}
		}
	}
	static string toOperations(string &str, vector<Lexemes> &O){
		for (short j = 0; j < str.length() - 1; j++) str[j] = str[j + 1];
		str.pop_back();
		int page = toInt(str);
		for (int j = 0; j < O.size(); j++){
			if (page - 1 == j){
				if (O[j].StrCmp("^")) return "**";
				else return O[j].Get();
			}
		}
	}
	static string toIdentificator(string &str, vector<Lexemes> &I){
		for (short j = 0; j < str.length() - 1; j++) str[j] = str[j + 1];
		str.pop_back();
		int page = toInt(str);
		for (int j = 0; j < I.size(); j++){
			if (page - 1 == j){
				return I[j].Get();
			}
		}
	}
	static string toInteger_Constants(string &str, vector<Lexemes> &N){
		for (short j = 0; j < str.length() - 1; j++) str[j] = str[j + 1];
		str.pop_back();
		int page = toInt(str);
		for (int j = 0; j < N.size(); j++){
			if (page - 1 == j){
				return N[j].Get();
			}
		}
	}
	static string toCharecter_Constants(string &str, vector<Lexemes> &C){
		for (short j = 0; j < str.length() - 1; j++) str[j] = str[j + 1];
		str.pop_back();
		int page = toInt(str);
		for (int j = 0; j < C.size(); j++){
			if (page - 1 == j){
				return C[j].Get();
			}
		}
	}
};