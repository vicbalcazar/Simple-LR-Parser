//Author: Victor G. Balcazar
//Contact Info: victorbalcazar3@hotmail.com
//CPSC323: Project 9 - LR parser



#include <iostream>
#include <string>
#include "lrParser.h"

using namespace std;

int main() {
	string tape;
	cout << "Enter a string: \n";
	getline(cin, tape);

	checkTape(tape);

	system("pause");
	return 0;
}