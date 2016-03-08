#include "btfunctions.h"

#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

bool btcd(const string& newDirectory)
{
	//int status = chdir(newDirectory.c_str());
	path p(newDirectory);
	if (is_directory(p)) {
		return false;
	}
	try {
		boost::filesystem::current_path(newDirectory);
		return true;
	} catch (...) {
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
