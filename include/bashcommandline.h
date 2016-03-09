#ifndef BASHCOMMANDLINE_H
#define BASHCOMMANDLINE_H

#include <string>

#define MISTAKE_COUNT_HINT 5

using namespace std;

//gets the user input with a bash-like command line
string getBashInput();
//errors until the user enters the correct input, gives a hint after MISTAKE_COUNT_HINT incorrect guessed
string getBashInputExpected(const string& expected, const string& incorrectMessage = "Incorrect", const string& hintMessage = "Looks lilke you need a hint.");

#endif
