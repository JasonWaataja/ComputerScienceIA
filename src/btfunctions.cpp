#include "btfunctions.h"

#include <unistd.h>
#include <iostream>

using namespace std;

bool btcd(const string& newDirectory)
{
	int status = chdir(newDirectory.c_str());
	if (status == 0) {
		return true;
	} else {
		cerr << "Error, couldn't chage directory to " << newDirectory << endl;
		return false;
	}
}

bool blankFunction()
{
	return false;
}

function<bool()> getBtFunction(const string& name, int argc, char** argv)
{
	function<bool()> btFunction;
	if (name == "btcd") {
		if (argc >= 1) {
			//note, I try to have it copy it into a new string so the argument is still around
			string newDir = argv[0];
			btFunction = [newDir](){return btcd(newDir);};
		} else {
			cerr << "Error, btcd required at least one argument" << endl;
			btFunction = blankFunction;
		}
	} else {
		btFunction = blankFunction;
	}
	return btFunction;
}
