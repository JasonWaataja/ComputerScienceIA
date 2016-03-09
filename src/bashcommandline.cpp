#include "bashcommandline.h"

#include <readline/readline.h>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace boost::filesystem;
using namespace std;


BashCommandLine::BashCommandLine() : username("user"), computerName("computer")
{
	//rl_readline_name = "BashCommandLine";
	//more stuff here
}

BashCommandLine::~BashCommandLine()
{
}

string BashCommandLine::getPrompt()
{
	stringstream promptStream;

	promptStream << "[" << this->username << "@" << this->computerName << " ";

	path currentDir = current_path();
	char* home;
	home = getenv("HOME");
	bool inHome = false;
	if (home) {
		if (currentDir == path(home)) {
			inHome = true;
		}
	}
	if (inHome)
		promptStream << "~";
	else
		promptStream << currentDir.string();

	promptStream << "]$ ";
	return promptStream.str();
}

string BashCommandLine::getBashInput()
{
	string prompt = this->getPrompt();
	char* line = readline(prompt.c_str());
	string input = line;
	free(line);
	return input;
}

string BashCommandLine::getBashInputExpected(const string& expected, const string& incorrectMessage, const string& hintMessage)
{
}

string BashCommandLine::getUsername() const
{
	return this->username;
}

void BashCommandLine::setUsername(const string& username)
{
	this->username = username;
}

string BashCommandLine::getComputerName() const
{
	return this->computerName;
}

void BashCommandLine::setComputerName(const string& computerName)
{
	this->computerName = computerName;
}
