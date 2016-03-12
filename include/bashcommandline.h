#ifndef BASHCOMMANDLINE_H
#define BASHCOMMANDLINE_H

#include <string>

#define MISTAKE_COUNT_HINT 5

using namespace std;

class BashCommandLine
{
	private:
		string username;
		string computerName;

	public:
		BashCommandLine();
		BashCommandLine(const string& username, const string& computerName);
		~BashCommandLine();

		string getPrompt();


		//gets the user input with a bash-like command line
		string getBashInput();
		//errors until the user enters the correct input, gives a hint after MISTAKE_COUNT_HINT incorrect guessed
		string getBashInputExpected(const string& expected, const string& incorrectMessage = "Incorrect, try again");
		string getBashInputExpected(const string& expected, const string& incorrectMessage, const string& hintMessage);

		string getUsername() const;
		void setUsername(const string& username);
		string getComputerName() const;
		void setComputerName(const string& computerName);
};

#endif
