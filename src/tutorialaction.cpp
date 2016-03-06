#include "tutorialaction.h"

#include <iostream>
#include <string>
#include <string.h>
#include <functional>
#include <vector>
#include "btfunctions.h"

using namespace std;

TutorialAction::TutorialAction(const function<bool()>& action) : action(action)
{
}

TutorialAction::TutorialAction() 
{
	action = [](){cout<<"This is an action"<<endl;return true;};
}

TutorialAction::TutorialAction(const string& line)
{
	loadFromString(line);
}

bool TutorialAction::execute()
{
	return action();
}

bool TutorialAction::loadFromString(const string& line)
{
	action = blankFunction;
	vector<string> tokens;
	char* lineAsCString = new char[strlen(line.c_str()) + 1];
	strcpy(lineAsCString, line.c_str());
	char* currentToken;
	currentToken = strtok(lineAsCString, " ");
	while (currentToken != NULL)
	{
		tokens.push_back(currentToken);
		currentToken = strtok(NULL, " ");
	}
	int tokenCount = tokens.size();
	if (tokenCount > 0)
	{
		string firstWord = tokens[0];

		if (firstWord == "print") {
			//start at the position after print plus one space
			int startPos = line.find("print") + strlen("print ");
			string messageToPrint = line.substr(startPos, line.length() - startPos);
			//copy instead of reference hopefull, so preserved
			action = [messageToPrint](){cout << messageToPrint << endl;return true;};
		} else {

			int argc = tokenCount - 1;
			char** argv = new char*[argc];
			for (int i = 0; i < argc; i++) {
				string currentToken = tokens[i+1];
				char* token = new char[strlen(currentToken.c_str())+1];
				strcpy(token, currentToken.c_str());
				argv[i] = token;
			}

			action = getBtFunction(firstWord, argc, argv);

			for (int i = 0; i < argc; i++) {
				delete[] argv[i];
			}
			delete[] argv;
		}
	}
	delete[] lineAsCString;
	//always succeeds for now
	return true;
}
