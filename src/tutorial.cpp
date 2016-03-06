#include "tutorial.h"

#include <fstream>
#include <iostream>

using namespace std;

bool fileHasExtension(const string& path, const string& extension)
{
	size_t extensionPos = path.find_last_of(".") + 1;
	//if there's not dot
	if (extensionPos == string::npos) {
		return false;
	} else {
		string fileExtension = path.substr(extensionPos, path.length() - extensionPos);
		if (fileExtension == extension) {
			return true;
		} else {
			return false;
		}
	}
}

Tutorial::Tutorial() : MenuEntry("Tutorial", "a tutorial")
{
}

Tutorial::~Tutorial()
{
}

bool Tutorial::loadFromFile(const string& path)
{
	ifstream reader;
	reader.open(path);
	if (reader.is_open()) {
		string line;
		//while (getline(reader, line) != 
	}
}
