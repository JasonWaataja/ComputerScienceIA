#ifndef BTFUNCTIONS_H
#define BTFUNCTIONS_H

#include <string>
#include <functional>
#include <iostream>

using namespace std;

//bt cd function, calls glibc chdir internally
bool btcd(const string& newDirectory);

//blank function that always fails
bool blankFunction();

//returns pointer to the function corresponding to the string, returns null if could not be found
function<bool()> getBtFunction(const string& name, int argc, char** argv);

#endif
