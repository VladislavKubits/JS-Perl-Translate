#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

class Tab_of_states{

private:
	vector<string> field;

public:
	Tab_of_states(ifstream &file, int i, int j){
		if (i == 0 || j == 0) { 
			string str;
			getline(file, str, ' ');
			this->field.push_back(str);
		}
		else for (int k = 0; k < 4; k++){
			string str;
			getline(file, str, ' ');
			this->field.push_back(str);
		}
	}
	~Tab_of_states(){}

	bool if_tab_of_states(const string &str){
		if (this->field.front() == "N,C"){
			if (str[0] == 'N' || str[0] == 'C') return true;
		}
		if (this->field.front() == "I"){
			if (str[0] == 'I') return true;
		}
		if (this->field.front() == "("){
			if (str == "R11") return true;
		}
		if (this->field.front() == ")"){
			if (str == "R12") return true;
		}
		if (this->field.front() == "]"){
			if (str == "R8") return true;
		}
		if (this->field.front() == ","){
			if (str == "R4") return true;
		}
		if (this->field.front() == ";"){
			if (str == "R5") return true;
		}
		if (this->field.front() == "/n"){
			if (str == "\n") return true;
		}
		if (this->field.front() == "IF"){
			if (str == "W7") return true;
		}
		if (this->field.front() == "{"){
			if (str == "R9") return true;
		}
		if (this->field.front() == "else"){
			if (str == "W8") return true;
		}
		if (this->field.front() == "PROC"){
			if (str == "W4") return true;
		}
		if (this->field.front() == "var"){
			if (str == "W1") return true;
		}
		if (this->field.front() == "new"){
			if (str == "W2") return true;
		}
		if (this->field.front() == "Array"){
			if (str == "W3") return true;
		}
		if (this->field.front() == "return"){
			if (str == "W5") return true;
		}
		if (this->field.front() == "!else"){
			if (str != "W8") return true;
		}
		if (this->field.front() == "}"){
			if (str == "R10") return true;
		}
		if (this->field.front() == "="){
			if (str == "O1") return true;
		}
		if (this->field.front() == "goto"){
			if (str == "W6") return true;
		}
		if (this->field.front() == "Op6"){
			if (str == "O6" || str == "O7" || str == "O8" || str == "O9" || str == "O10" || str == "O11") return true;
		}
		if (this->field.front() == "Op7"){
			if (str == "O2" || str == "O3") return true;
		}
		if (this->field.front() == "Op8"){
			if (str == "O4" || str == "O12") return true;
		}
		if (this->field.front() == "Op9"){
			if (str == "O5") return true;
		}
		if (this->field.front() == ":"){
			if (str == "R6") return true;
		}
		if (this->field.front() == "["){
			if (str == "R7") return true;
		}
		if (this->field.front() == "!["){
			if (str != "R7") return true;
		}
		if (this->field.front() == "Others"){
			if (str != "R12" && str != "R11" && str[0] != 'N' && str[0] != 'C' && str[0] != 'I' && str != "R7") return true;
		}
	}

	bool if_tab_of_states(const stack<string> &st, int &if_i, int &proc_level){
		if (this->field.front() == "#"){
			if (st.size() == 0) return true;
		}
		if (st.size() > 0 && this->field.front() == "("){
			if (st.top() == "R11") return true;
		}
		if (st.size() > 0 && this->field.front() == "iA"){
			if (st.top().size() == 4 && st.top()[0] > 48 && st.top()[1] == 'A' && st.top()[2] == 'E' && st.top()[3] == 'M') return true;
		}
		if (st.size() > 0 && this->field.front() == "iF"){
			if (st.top().size() == 2 && st.top()[0] > 48 && (st.top()[1] == 'F' || st.top()[1] == 'T' || st.top()[1] == 'A')) return true;
		}
		if (st.size() > 0 && this->field.front() == "IF"){
			if (st.top() == "W7") return true;
		}
		if (st.size() > 0 && this->field.front() == "1IF"){
			if (st.top() == "1W7") return true;
		}
		if (st.size() > 0 && this->field.front() == "!MiIF"){
			if (st.top().size() == 5 && st.top()[0] == '!' && st.top()[1] == 'M' && st.top()[2] % 2 == 1 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "0MiIF"){
			if (st.top().size() == 5 && st.top()[0] == '0' && st.top()[1] == 'M' && st.top()[2] % 2 == 1 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "MiIF"){
			if (st.top().size() == 5 && st.top()[1] == 'M' && st.top()[2] % 2 == 1 && st.top()[3] == 'W' && st.top()[4] == '7') return true;
		}
		if (st.size() > 0 && this->field.front() == "1MiIF"){
			if (st.top().size() == 5 && st.top()[0] == '1' && st.top()[1] == 'M' && st.top()[2] % 2 == 1 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "!Mi+1IF"){
			if (st.top().size() == 5 && st.top()[0] == '!' && st.top()[1] == 'M' && st.top()[2] % 2 == 0 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "0Mi+1IF"){
			if (st.top().size() == 5 && st.top()[0] == '0' && st.top()[1] == 'M' && st.top()[2] % 2 == 0 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "Mi+1IF"){
			if (st.top().size() == 5 && st.top()[1] == 'M' && st.top()[2] % 2 == 0 && st.top()[3] == 'W' && st.top()[4] == '7') return true;
		}
		if (st.size() > 0 && this->field.front() == "1Mi+1IF"){
			if (st.top().size() == 5 && st.top()[0] == '1' && st.top()[1] == 'M' && st.top()[2] % 2 == 0 && st.top()[3] == 'W' && st.top()[4] == '7') 
				return true;
		}
		if (st.size() > 0 && this->field.front() == "i,jProc"){
			if (st.top().size() == 4 && st.top()[1] == proc_level + 48 && st.top()[2] == 'W' && st.top()[3] == '4') return true;
		}
		if (st.size() > 0 && this->field.front() == "i,j,kD"){
			if (st.top().size() == 5 && st.top()[1] == proc_level + 48 && st.top()[3] == 'W' && st.top()[4] == '1') return true;
		}
		if (st.size() > 0 && this->field.front() == "{"){
			if (st.top() == "R9") return true;
		}
		if (st.size() > 0 && this->field.front() == "="){
			if (st.top() == "O1") return true;
		}
		if (st.size() > 0 && this->field.front() == "goto"){
			if (st.top() == "W6") return true;
		}
		if (st.size() > 0 && this->field.front() == "new"){
			if (st.top() == "W2") return true;
		}
		if (st.size() > 0 && this->field.front() == "Array"){
			if (st.top() == "W3") return true;
		}
		if (st.size() > 0 && this->field.front() == "return"){
			if (st.top() == "W5") return true;
		}
		if (st.size() > 0 && this->field.front() == "Op6"){
			if (st.top() == "O6" || st.top() == "O7" || st.top() == "O8" || st.top() == "O9" || st.top() == "O10" || st.top() == "O11") return true;
		}
		if (st.size() > 0 && this->field.front() == "Op7"){
			if (st.top() == "O2" || st.top() == "O3") return true;
		}
		if (st.size() > 0 && this->field.front() == "Op8"){
			if (st.top() == "O4" || st.top() == "O12") return true;
		}
		if (st.size() > 0 && this->field.front() == "Op9"){
			if (st.top() == "O5") return true;
		}
		if (st.size() > 0 && this->field.front() == "1F"){
			if (st.top() == "1F" || st.top() == "1T" || st.top() == "1A") return true;
		}
		if (this->field.front() == "Others"){
			if (st.size() == 0) return true;
			else if (st.top() != "1F" && st.top() != "1T" && st.top() != "1A" && st.top() != "W3" && 
				(st.top().size() != 4 || st.top()[1] != proc_level + 48 || st.top()[2] != 'W' || st.top()[3] != '4')) return true;
		}
	}

	void doing(const string &str, ofstream &file, stack<string> &st, bool &STOP, bool &ERR, int &this_state, int &if_i, 
		int &proc_num, int &proc_level, int &var_num){
		STOP = false;
		for (short i = 0; i < 4; i++){
			if (this->field[i] == "N") 
				break;
			if (this->field[i] == "Out(X)") {
				file << str << ' ';
				continue;
			}
			if (this->field[i] == "Out(A)") {
				file << st.top()[0] << st.top()[1] << st.top()[2] << st.top()[3] << ' ';
				continue;
			}
			if (this->field[i] == "Out(F)") {
				file << st.top()[0] << st.top()[1] << ' ';
				continue;
			}
			if (this->field[i] == "Out(:)") {
				file << "R6 ";
				continue;
			}
			if (this->field[i] == "Out(goto)") {
				file << "¡œ ";
				continue;
			}
			if (this->field[i] == "Out"){
				file << st.top() << ' ';
				continue;
			}
			if (this->field[i] == "Out(Mi”œÀ)"){
				file << 'M' << (char)(if_i + 2 + 48) << " ”œÀ ";
				++proc_level;
				continue;
			}
			if (this->field[i] == "Out(Mi+1BPMi:)"){
				file << 'M' << (char)(st.top()[2] + 1) << " ¡œ M" << st.top()[2] << ": ";
				continue;
			}
			if (this->field[i] == "Out(Mi:)"){
				file << st.top()[1] << st.top()[2] << ": ";
				--proc_level;
				continue;
			}
			if (this->field[i] == "Out(i,jÕœ:)"){
				file << st.top()[0] << st.top()[1] << "Õœ ";
				++proc_level;
				continue;
			}
			if (this->field[i] == "Out(i,j œ:)"){
				file << " œ ";
				--proc_level;
				continue;
			}
			if (this->field[i] == "Out( Œ)"){
				file << st.top()[0] << st.top()[1] << st.top()[2] << " Œ ";
				continue;
			}
			if (this->field[i] == "/n") {
				file << endl << ' ';
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
			if (this->field[i] == "St(2)"){
				this_state = 2;
				continue;
			}
			if (this->field[i] == "St(3)"){
				this_state = 3;
				continue;
			}
			if (this->field[i] == "Push") {
				st.push(str);
				continue;
			}
			if (this->field[i] == "Pop") {
				st.pop();
				continue;
			}
			if (this->field[i] == "Stop") {
				STOP = true;
				continue;
			}
			if (this->field[i] == "Change(i+1A)" || this->field[i] == "Change(i+1F)"){
				++st.top()[0];
				continue;
			}
			if (this->field[i] == "Cange(2F)"){
				st.top()[0] = '2';
				continue;
			}
			if (this->field[i] == "Change(!MiIF)"){
				st.top() = "!M0W7";
				if_i += 2;
				st.top()[2] = if_i + 48;
				continue;
			}
			if (this->field[i] == "Change(0MiIF)"){
				st.top()[0] = '0';
				continue;
			}
			if (this->field[i] == "Change(1MiIF)"){
				st.top()[0] = '1';
				continue;
			}
			if (this->field[i] == "Change(!Mi+1IF)"){
				st.top()[0] = '!';
				++st.top()[2];
				continue;
			}
			if (this->field[i] == "Change(0Mi+1IF)"){
				st.top()[0] = '0';
				continue;
			}
			if (this->field[i] == "Change(1Mi+1IF)"){
				st.top()[0] = '1';
				continue;
			}
			if (this->field[i] == "Change(1IF)"){
				st.top() = "1W7";
				continue;
			}
			if (this->field[i] == "Change(i,j,k+1D)"){
				++st.top()[2];
				continue;
			}
			if (this->field[i] == "Push(1F)"){
				st.push("1F");
				continue;
			}
			if (this->field[i] == "Push(1A)"){
				st.push("1A");
				continue;
			}
			if (this->field[i] == "Push(1T)"){
				st.push("1T");
				continue;
			}
			if (this->field[i] == "Push(2A)"){
				st.push("2AEM");
				continue;
			}
			if (this->field[i] == "Push(i,jProc)"){
				string this_str = "1234";
				++proc_num;
				this_str[0] = proc_num + 48;
				this_str[1] = proc_level + 48;
				this_str[2] = 'W';
				this_str[3] = '4';
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Push(i,j,1D)"){
				string this_str = "12345";
				++var_num;
				this_str[0] = var_num + 48;
				this_str[1] = proc_level + 48;
				this_str[2] = '1';
				this_str[3] = 'W';
				this_str[4] = '1';
				st.push(this_str);
				continue;
			}
			if (this->field[i] == "Err") {
				file << "ERROR" << ' ';
				ERR = true;
				break;
			}
		}
	}
};