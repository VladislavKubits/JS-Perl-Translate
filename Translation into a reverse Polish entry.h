#pragma once

#include <iostream>
#include "Tab_of_states.h"
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

void Conversion_to_IPF(bool ERR)
{

	ofstream res("IPF.txt");
	if (ERR) {
		res << "ERROR ";
		res.close();
		return;
	}
	else {
#define TAB_OF_STATES_0_SIZE1 28
#define TAB_OF_STATES_0_SIZE2 29
#define TAB_OF_STATES_1_SIZE1 5
#define TAB_OF_STATES_1_SIZE2 8
#define TAB_OF_STATES_2_SIZE1 2
#define TAB_OF_STATES_2_SIZE2 4
#define TAB_OF_STATES_3_SIZE1 2
#define TAB_OF_STATES_3_SIZE2 3

		setlocale(LC_ALL, "");
		int tab_of_size[4][2] = { TAB_OF_STATES_0_SIZE1, TAB_OF_STATES_0_SIZE2,
			TAB_OF_STATES_1_SIZE1, TAB_OF_STATES_1_SIZE2,
			TAB_OF_STATES_2_SIZE1, TAB_OF_STATES_2_SIZE2,
			TAB_OF_STATES_3_SIZE1, TAB_OF_STATES_3_SIZE2 };

		Tab_of_states *tab_of_st[4][TAB_OF_STATES_0_SIZE1][TAB_OF_STATES_0_SIZE2];
		ifstream Tos("Tab_of_states.txt");
		string str;
		for (short k = 0; k < 4; k++) {
			for (int i = 0; i < tab_of_size[k][0]; i++) {
				for (int j = 0; j < tab_of_size[k][1]; j++)
					tab_of_st[k][i][j] = new Tab_of_states(Tos, i, j);
				Tos.seekg(2, ios::cur);
			}
			Tos.seekg(2, ios::cur);
		}

		Tos.close();
		ifstream js_code("internal representation of lexemes.txt");
		int this_state = 0;
		stack<string> st;

		bool STOP = false;
		int if_i = -1, proc_num = 0, proc_level = 1, var_num = 0;
		while (!ERR) {

			if (!STOP) getline(js_code, str, ' ');
			for (int i = 1; i < tab_of_size[this_state][0]; i++)
				if (tab_of_st[this_state][i][0]->if_tab_of_states(st, if_i, proc_level)) {
					for (int j = 1; j < tab_of_size[this_state][1]; j++)
						if (tab_of_st[this_state][0][j]->if_tab_of_states(str)) {
							tab_of_st[this_state][i][j]->doing(str, res, st, STOP, ERR, this_state, if_i, proc_num, proc_level, var_num);
							break;
						}
					break;
				}
			if (str == "") break;
		}

		while (st.size() > 0 && !ERR) {
			if (st.top() == "W6") { res << "ÁÏ" << ' '; st.pop(); continue; }
			if (st.top()[1] == 'M' && (st.top()[2] % 2 == 1 || st.top()[2] % 2 == 0) && st.top()[3] == 'W' && st.top()[4] == '7') {
				res << 'M' << st.top()[2] << ": ";
				st.pop(); continue;
			}
			if (st.top().size() == 5 && st.top()[1] == proc_level + 48 && st.top()[3] == 'W' && st.top()[4] == '1') {
				res << st.top()[0] << st.top()[1] << st.top()[2] << "ÊÎ ";
				st.pop(); continue;
			}
			else {
				res << st.top() << ' ';
				st.pop(); continue;
			}
		}
		res.close();
		js_code.close();
	}
}