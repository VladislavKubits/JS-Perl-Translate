#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "Convert to Perl.h"

using namespace std;

class Tab_of_actions{

private:
	vector<string> field;

public:
	Tab_of_actions(ifstream &file, int i){
		if (i == 0) {
			string str;
			getline(file, str, ' ');
			this->field.push_back(str);
		}
		else for (int k = 0; k < 2; k++){
			string str;
			getline(file, str, ' ');
			this->field.push_back(str);
		}
	}
	~Tab_of_actions(){}

	static void Push(stack<string>& st, string &this_str){
		if (st.top()[0] != '@' && st.top()[0] != '(' && st.top()[0] != '$' && (st.top()[0] < 48 || st.top()[0] > 57) &&
			st.top()[0] != 34){
			this_str.push_back('$');
			for (short i = 0; i < st.top().length(); i++) this_str.push_back(st.top()[i]);
			st.pop();
		}
		else {
			for (short i = 0; i < st.top().length(); i++) this_str.push_back(st.top()[i]);
			st.pop();
		}
	}

	bool if_tab_of_actions(const string &str, stack<int> &st_if_i, int &if_i){
		if (this->field.front() == "N,C,I"){
			if (str[0] == 'N' || str[0] == 'C' || str[0] == 'I') return true;
		}
		if (this->field.front() == "ÍÏ"){
			if (str.length() == 4 && str[2] == 'Í' && str[3] == 'Ï') return true;
		}
		if (this->field.front() == "ÊÏ"){
			if (str == "ÊÏ") return true;
		}
		if (this->field.front() == "ÊÎ"){
			if (str.length() == 5 && str[3] == 'Ê' && str[4] == 'Î') return true;
		}
		if (this->field.front() == "ÓÏË"){
			if (str == "ÓÏË") return true;
		}
		if (this->field.front() == "ÁÏ"){
			if (str == "ÁÏ") return true;
		}
		if (this->field.front() == ":"){
			if (str == "R6") return true;
		}
		if (this->field.front() == "O"){
			if (str[0] == 'O' && str != "O1") return true;
		}
		if (this->field.front() == "="){
			if (str == "O1") return true;
		}
		if (this->field.front() == "iF"){
			if (str[1] == 'F') return true;
		}
		if (this->field.front() == "iT"){
			if (str[1] == 'T') return true;
		}
		if (this->field.front() == "iA"){
			if (str.length() == 2 && str[1] == 'A') return true;
		}
		if (this->field.front() == "iAEM"){
			if (str.length() == 4 && str[1] == 'A' && str[2] == 'E' && str[3] == 'M') return true;
		}
		if (this->field.front() == "Mi"){
			if (str.length() == 2 && str[0] == 'M') { if_i = (int)str[1] - 48; return true; }
		}
		if (this->field.front() == "Mi:"){
			if (str.length() == 3 && str[0] == 'M' && st_if_i.top() == str[1] - 48) return true;
		}
		if (this->field.front() == "Mi+1:"){
			if (str.length() == 3 && str[0] == 'M' && st_if_i.top() == str[1] - 49) { st_if_i.pop();  return true; }
		}
		if (this->field.front() == "return"){
			if (str == "W5") return true;
		}
		if (this->field.front() == "/n"){
			if (str == "\n") return true;
		}
	}

	void doing(string &str, ofstream &file, stack<string> &st, bool &ERR, vector<Lexemes> &W, vector<Lexemes> &I, vector<Lexemes> &O,
		vector<Lexemes> &N, vector<Lexemes> &C, short &this_state, bool &STOP, stack<int> &st_if_i, int &if_i){
		for (short i = 0; i < 2; i++){
			STOP = false;
			if (this->field[i] == "N")
				break;
			if (this->field[i] == "Push") {
				if (str[0] == 'I') st.push(Convert::toIdentificator(str, I));
				if (str[0] == 'N') st.push(Convert::toInteger_Constants(str, N));
				if (str[0] == 'C') st.push(Convert::toCharecter_Constants(str, C));
				continue;
			}
			if (this->field[i] == "Push_rp"){
				string this_str, this_str2;
				this_str.push_back('(');
				Push(st, this_str2);
				Push(st, this_str);

				this_str.push_back(' ');
				str = Convert::toOperations(str, O);
				for (short i = 0; i < str.length(); i++) this_str.push_back(str[i]);
				this_str.push_back(' ');

				for (short i = 0; i < this_str2.length(); i++) this_str.push_back(this_str2[i]);
				this_str.push_back(')');
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push_@"){
				int page = str[0] - 48;
				stack<string> vec;
				for (int i = str[0] - 48; i > 1; i--){
					vec.push(st.top());
					st.pop();
				}
				string this_str;
				this_str.push_back('@');
				for (short i = 0; i < st.top().length(); i++) this_str.push_back(st.top()[i]);
				st.pop();
				this_str.push_back('[');
				while (vec.size() != 0) {
					Push(vec, this_str);
					this_str.push_back(',');
				}
				this_str.back() = ']';
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push_{"){
				st.top().push_back('{');
				continue;
			}
			if (this->field[i] == "Push_}"){
				if(st.size() > 0)st.top().push_back('}');
				else st.push("}");
				continue;
			}
			if (this->field[i] == "Push_if"){
				string this_str = "if";
				Push(st, this_str);
				this_str.push_back('{');
				st.push(this_str);
				st_if_i.push(if_i);
				continue;
			}
			if (this->field[i] == "Push_GOTO"){
				string this_str = "goto ";
				for (short j = 0; j < st.top().length(); j++) this_str.push_back(st.top()[j]);
				this_str.push_back(';');
				st.top() = this_str;
				continue;
			}
			if (this->field[i] == "Push_RETURN"){
				string this_str = "return ";
				for (short j = 0; j < st.top().length(); j++) this_str.push_back(st.top()[j]);
				this_str.push_back(';');
				st.top() = this_str;
				continue;
			}
			if (this->field[i] == "Push_ELSE"){
				string this_str = "} else {";
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push_BP"){
				st.top().push_back(':');
				continue;
			}
			if (this->field[i] == "Push_RP"){
				string this_str1, this_str2 = st.top();
				st.pop();
				Push(st, this_str1);
				this_str1.push_back('=');
				for (int j = 0; j < this_str2.length(); j++) this_str1.push_back(this_str2[j]);
				st.push(this_str1);
				continue;
			}
			if (this->field[i] == "Push_&"){
				int page = str[0] - 48;
				stack<string> vec;
				for (int i = str[0] - 48; i > 1; i--){
					vec.push(st.top());
					st.pop();
				}
				string this_str;
				this_str.push_back('&');
				for (short i = 0; i < st.top().length(); i++) this_str.push_back(st.top()[i]);
				st.pop();
				this_str.push_back('(');
				while (vec.size() != 0) {
					Push(vec, this_str);
					this_str.push_back(',');
				}
				this_str.back() = ')';
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push_SUB"){
				string this_str = "sub ";
				int page = str[0] - 48;
				stack<string> vec;
				for (int i = str[0] - 48; i > 1; i--){
					vec.push(st.top());
					st.pop();
				}
				for (short i = 0; i < st.top().length(); i++) this_str.push_back(st.top()[i]);
				st.pop();
				this_str.push_back('(');
				while (vec.size() != 0) {
					Push(vec, this_str);
					this_str.push_back(',');
				}
				this_str.back() = ')';
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push_KO"){
				int page = str[2] - 48;
				stack<string> vec;
				for (int i = str[2] - 48; i > 0; i--){
					vec.push(st.top());
					st.pop();
				}
				string this_str;
				while (vec.size() != 0) {
					Push(vec, this_str);
					this_str.push_back(',');
				}
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Out"){
				if (st.size() == 0) continue;
				if (st.top()[st.top().length() - 1] == ',') st.top()[st.top().length() - 1] = ';';
				if (st.top()[st.top().length() - 1] != ';' && st.top()[st.top().length() - 1] != '}' && st.top()[st.top().length() - 1] != '{'
					&& st.top()[st.top().length() - 1] != ')' && st.top()[st.top().length() - 1] != ':') st.top().push_back(';');
				stack<string> output;
				for (int j = 0; j < st.size()+1; j++){
					output.push(st.top());
					st.pop();
				}
				for (int j = 0; j < output.size()+1; j++){
					file << output.top();
					output.pop();
				}
				file << endl;
				continue;
			}
			if (this->field[i] == "St(0)"){
				this_state = 0;
				continue;
			}
			if (this->field[i] == "St(1)"){
				this_state = 1;
				continue;
			}
			if (this->field[i] == "Pop"){
				st.pop();
				continue;
			}
			if (this->field[i] == "Stop") {
				STOP = true;
				continue;
			}
		}
	}
};