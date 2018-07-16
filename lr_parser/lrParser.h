#ifndef LRPARSER
#define	LRPARSER

#include <iostream>
#include <string>
#include <stack>
using namespace std;
//Rule set            1         2     3       4      5      6      7       8
string rules[8] = { "EE+T", "EE-T", "ET", "TT*F", "TT/F", "TF", "F(E)", "Fi" };
//Rule set index      0         1     2       3      4      5      6       7

//parsing table
string parTable[16][11] = {"S5", "_", "_", "_", "_", "S4", "_", "_", "1", "2", "3",			//0
						   "_", "S6", "S7", "_", "_", "_", "_", "acc", "_", "_", "_",		//1
						   "_", "R3", "R3", "S8", "S9", "_", "R3", "R3", "_", "_", "_",		//2
						   "_", "R6", "R6", "R6", "R6", "_", "R6", "R6", "_", "_", "_",		//3
						   "S5", "_", "_", "_", "_", "S4", "_", "_", "10", "2", "3",		//4
						   "_", "R8", "R8", "R8", "R8", "_", "R8", "R8", "_", "_", "_",		//5
						   "S5", "_", "_", "_", "_", "S4", "_", "_", "_", "11", "3",		//6
						   "S5", "_", "_", "_", "_", "S4", "_", "_", "_", "12", "3",		//7
						   "S5", "_", "_", "_", "_", "S4", "_", "_", "_", "_", "13",		//8
						   "S5", "_", "_", "_", "_", "S4", "_", "_", "_", "_", "14",		//9
						   "_", "S6", "S7", "_", "_", "_", "S15", "_", "_", "_", "_",		//10 
						   "_", "R1", "R1", "S8", "S9", "_", "R1", "R1", "_", "_", "_",		//11
						   "_", "R2", "R2", "S8", "S9", "_", "R2", "R2", "_", "_", "_",		//12
						   "_", "R4", "R4", "R4", "R4", "_", "R4", "R4", "_", "_", "_",		//13
						   "_", "R5", "R5", "R5", "R5", "_", "R5", "R5", "_", "_", "_",		//14
						   "_", "R7", "R7", "R7", "R7", "_", "R7", "R7", "_", "_", "_"};		//15

//possible values in language
char values[11] = { 'i', '+', '-', '*', '/', '(', ')', '$', 'E', 'T', 'F' };

bool visitedS = true; //did the last visit to the tab end with Sin [0]
bool accept = false;
bool visitedR = false;
stack <string> s;
string popped;
string read;
string judged;
string rule;
string nextStep;
int i, j = 0;
string temp;

bool valInLanguage(char c) {
	for (int i = 0; i < 11; i++) {
		if (c == values[i]) {
			return true;
		}
	}
	return false;
}

int determine_val(char st) {
	for (int i = 0; i < 11; i++) {
		if (values[i] == st) {
			return i;
		}
	}
}

bool checkTape(string tape) {
	for (int i = 0; i < tape.size(); i++) {
		if (!valInLanguage(tape[i])) {
			cout << "rejected" << endl;
			return false;
		}
	}

	if (tape[tape.size() - 1] != '$') {
		tape += "$";
		cout << tape << endl;
	}


	int tape_cnt = 0;


	s.push("0");

	while (tape_cnt < tape.size()+1) {
		if (visitedS) {
			read = tape[tape_cnt];
			tape_cnt++;
			cout << "read: " << read << endl;
		}
		popped = s.top();
		s.pop();
		cout << "popped: " << popped << endl;

		if (visitedR == false) {
			judged = read[0];
		}
		
		nextStep = parTable[atoi(popped.c_str())][determine_val(judged[0])];
		cout << "[" << popped.c_str() << "] [" << determine_val(judged[0]) << "]: " << nextStep << endl;
		if (nextStep[0] == 'S') {
			visitedS = true;
			s.push(popped);
			s.push(judged);
			temp = nextStep[1];
			if (nextStep.size() > 2)
				temp += nextStep[2];
			s.push(temp);
			cout << "push: " << popped << " " << judged << " " << temp << endl;
		}
		else if (nextStep[0] == 'R') {
			visitedS = false;
			visitedR = true;
			s.push(popped);
			cout << "push" << popped << endl;
			temp = nextStep[1];
			rule = rules[atoi(temp.c_str()) - 1];
			cout << "rule: " << rule;
			i = ( 2 * (rule.size() - 1));
			cout << " to be popped " << i << endl;
			for (j = 0; j < i; j++) {
				s.pop();
			}
			judged = rule[0];
		}
		else if (isdigit(nextStep[0])) {
			s.push(popped);
			s.push(judged);
			s.push(nextStep);
			cout << "pushed: " << popped << " " << judged << " " << nextStep << endl;
			visitedR = false;
		}
		else if (nextStep == "acc") {
			cout << "accepted \n";
			return true;
		}
		else if (nextStep == "_") {
			cout << "rejected\n";
			return false;
		}
		

	}

	cout << "rejected\n";
	return false;
}


#endif // !LRPARSER
