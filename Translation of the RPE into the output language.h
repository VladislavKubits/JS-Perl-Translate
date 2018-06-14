#pragma once

#include "Lexemes.h"
#include "Tab_of_action.h"

void Convert_to_Perl_code(bool &ERR) {

	ofstream perl("Perl_code.txt");

	if (ERR) {
		perl << "ERROR ";
		perl.close();
		return;
	}
	else {
#define TAB_OF_ACTIONS_SIZE 18

		Tab_of_actions *tab_of_act[2][2][TAB_OF_ACTIONS_SIZE];
		ifstream Toa("Tab of action.txt");
		for (short k = 0; k < 2; k++) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < TAB_OF_ACTIONS_SIZE; j++) tab_of_act[k][i][j] = new Tab_of_actions(Toa, i);
				Toa.seekg(2, ios::cur);
			}
			Toa.seekg(2, ios::cur);
		}
		Toa.close();

		ifstream function_words("Function words.txt"); //служебные слова
		ifstream operations("Operations 2.txt"); //операции
		ifstream identifier("Identifier.txt"); //идентификаторы
		ifstream int_const("Integer_Constants.txt"); //числовые константы
		ifstream char_const("Charecter_Constants.txt"); //строковые константы

		string this_str;
		stack<string> st;
		vector<Lexemes> W, I, O, N, C;
		Lexemes lex; //лексема, €вл€юща€с€ буффером при чтении из файла

		while (!function_words.eof()) {
			lex.Set_from_file(function_words);
			W.push_back(lex);
		}
		while (!operations.eof()) {
			lex.Set_from_file(operations);
			O.push_back(lex);
		}
		while (!identifier.eof()) {
			lex.Set_from_file(identifier);
			I.push_back(lex);
		}
		while (!int_const.eof()) {
			lex.Set_from_file(int_const);
			N.push_back(lex);
		}
		while (!char_const.eof()) {
			lex.Set_from_file(char_const);
			C.push_back(lex);
		}

		ifstream IPF("IPF.txt");
		short this_state = 0;
		stack<int> st_if_i;
		int if_i;
		bool STOP = false;

		perl << "#!/usr/bin/perl" << endl;

		while (!IPF.eof()) {
			if (!STOP) getline(IPF, this_str, ' ');
			if (this_str == "") break;

			for (int i = 0; i < TAB_OF_ACTIONS_SIZE; i++)
				if (tab_of_act[this_state][0][i]->if_tab_of_actions(this_str, st_if_i, if_i)) {
					tab_of_act[this_state][1][i]->doing(this_str, perl, st, ERR, W, I, O, N, C, this_state, STOP, st_if_i, if_i);
					break;
				}
		}

		if (st.size() > 0) {
			if (st.top()[st.top().length() - 1] == ',') st.top()[st.top().length() - 1] = ';';
			if (st.top()[st.top().length() - 1] != ';' && st.top()[st.top().length() - 1] != '}' && st.top()[st.top().length() - 1] != '{'
				&& st.top()[st.top().length() - 1] != ')' && st.top()[st.top().length() - 1] != ':') st.top().push_back(';');
			stack<string> output;
			for (int j = 0; j < st.size() + 1; j++) {
				output.push(st.top());
				st.pop();
			}
			for (int j = 0; j < output.size() + 1; j++) {
				perl << output.top();
				output.pop();
			}
			perl << endl;
		}

		perl << "unlink 0;" << endl;

		IPF.close();
		perl.close();
		function_words.close();
		operations.close();
		identifier.close();
		int_const.close();
		char_const.close();
	}
}