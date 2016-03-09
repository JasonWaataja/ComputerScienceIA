#include "tutorialaction.h"

#include <iostream>
#include <string>
#include <string.h>
#include <functional>
#include <vector>
#include <cstdlib>
#include "btfunctions.h"
#include "bashcommandline.h"

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

int findQuoted(const string& parameter, string& quote, int start)
{
	int q1 = parameter.find('"', start);
	if (q1 == string::npos)
		return -1;
	start = q1+1;
	int q2;
	bool found = false;
	while (!found) {
		q2 = parameter.find('"', start);
		if (q2 == string::npos)
			return -1;
		start = q2+1;
		//if not escaped
		if (parameter[q2-1] != '\\')
			found = true;
	}
	int length = q2 - q1 - 1;
	quote = parameter.substr(q1+1, length);
	cout << parameter << endl;
	cout << quote << endl;
	cout << q1 << " " << q2 << endl;
	return q2 + 1;
}

function<bool()> getGeFunction(const string& parameter)
{
	function<bool()> action = [](){BashCommandLine b; b.getBashInput();return true;};
	string expectedInput;
	int pos1 = findQuoted(parameter, expectedInput);
	if (pos1 == -1)
		return action;
	string hint;
	int pos2 = findQuoted(parameter, hint, pos1);
	if (pos2 == -1)
		return action;
	action = [expectedInput, hint](){
		BashCommandLine b;
		b.getBashInputExpected(expectedInput, hint);
		return true;
	};
	return action;
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
		} else if (firstWord == "p") {
			int startPos = line.find("p") + strlen("p ");
			string messageToPrint = line.substr(startPos, line.length() - startPos);
			action = [messageToPrint](){cout << messageToPrint << endl;return true;};
		} else if (firstWord == "execute") {
			int startPos = line.find("execute") + strlen("execute ");
			string command = line.substr(startPos, line.length() - startPos);
			action = [command](){system(command.c_str());return true;};
		} else if (firstWord == "e") {
			//command starts on index 2, the third char of the line
			//int startPos = 2;
			int startPos = line.find("e") + strlen("e ");
			string command = line.substr(startPos, line.length() - startPos);
			action = [command](){system(command.c_str());return true;};
			//"get"
		} else if (firstWord == "g") {
			action = [](){BashCommandLine line;line.getBashInput(); return true;};
			//"get expected"
		}else if (firstWord == "ge") {
			int startPos = line.find("ge") + strlen("ge ");
			string parameter = line.substr(startPos, line.length() - startPos);
			action = getGeFunction(parameter);
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
