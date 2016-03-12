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

bool executeWithBash(const string& command)
{
	system(command.c_str());
	return true;
}

bool isEscaped(const string& s, int i)
{
	bool escaped = false;
	if (i >= 0 && i < s.length()) {
		if (i > 0) {
			char previous = s[i-1];
			if (previous != '\\') {
				return false;
			} else {
				isEscaped(s, i-1);
				return !isEscaped(s, i-1);
			}
		} else {
			return false;
		}
	}
	return false;
}


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
		//if (parameter[q2-1] != '\\')
		if (!isEscaped(parameter, q2))
			found = true;
	}
	int length = q2 - q1 - 1;
	quote = parameter.substr(q1+1, length);
	//cout << parameter << endl;
	//cout << quote << endl;
	//change to escaped characters.
	int i = 0;
	while (i < quote.length()) {
		if (isEscaped(quote, i)) {
			char c = quote[i];
			if (i == 'n')
				quote[i] = '\n';
			else if (c == 't')
				quote[i] = '\t';
			quote.erase(i-1, 1);
		} else {
			i++;
		}
	}
	return q2 + 1;
}

function<bool()> getGeFunction(const string& parameter)
{
}


function<bool()> getGeeFunction(const string& parameter)
{
	function<bool()> action = [](){BashCommandLine b; b.getBashInput();return true;};
	string expectedInput;
	int pos1 = findQuoted(parameter, expectedInput);
	if (pos1 == -1)
		return action;
	string errorMessage;
	int pos2 = findQuoted(parameter, errorMessage, pos1);
	if (pos2 == -1) {
		action = [expectedInput]() {
			BashCommandLine b;
			b.getBashInputExpected(expectedInput);
			executeWithBash(expectedInput);
			return true;
		};
		return action;
	}
	string hint;
	int pos3 = findQuoted(parameter, hint, pos2);
	if (pos3 == -1) {
		action = [expectedInput, errorMessage]() {
			BashCommandLine b;
			b.getBashInputExpected(expectedInput, errorMessage);
			executeWithBash(expectedInput);
			return true;
		};
		return action;
	}
	action = [expectedInput, errorMessage, hint](){
		BashCommandLine b;
		b.getBashInputExpected(expectedInput, errorMessage, hint);
		executeWithBash(expectedInput);
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
	delete[] lineAsCString;
	int tokenCount = tokens.size();
	//cout << tokenCount << endl;
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
		} else if (firstWord == "pw") {
			int startPos = line.find("pw") + strlen("pw ");
			string messageToPrint = line.substr(startPos, line.length() - startPos);
			action = [messageToPrint](){
				cout << messageToPrint << " ";
				string line;
				getline(cin, line);
				return true;

			};
		} else if (firstWord == "execute") {
			int startPos = line.find("execute") + strlen("execute ");
			string command = line.substr(startPos, line.length() - startPos);
			action = [command](){system(command.c_str());return true;};
		} else if (firstWord == "e") {
			//command starts on index 2, the third char of the line
			//int startPos = 2;
			int startPos = line.find("e") + strlen("e ");
			string command = line.substr(startPos, line.length() - startPos);
			action = [command](){executeWithBash(command);return true;};
			//"get"
		} else if (firstWord == "g") {
			action = [](){;BashCommandLine line;line.getBashInput(); return true;};
			//"get expected"
		}else if (firstWord == "ge") {
			int startPos = line.find("ge") + strlen("ge ");
			string parameter = line.substr(startPos, line.length() - startPos);
			action = getGeFunction(parameter);
		} else if (firstWord == "gee") {
			int startPos = line.find("gee") + strlen("gee ");
			string parameter = line.substr(startPos, line.length() - startPos);
			action = getGeeFunction(parameter);
		//w = "wait"
		} else if (firstWord == "w" || firstWord == "wait") {
			action = [](){
				cout << "Press ENTER to continue... ";
				string line;
				getline(cin, line);
				return true;
			};
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
	} else {
		return false;
	}
	//always succeeds for now
	return true;
}
