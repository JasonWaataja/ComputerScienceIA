#include <iostream>
#include <functional>
#include <cstdlib>
//#include <unistd.h>



#include "bashtutorial.h"
#include "tutorial.h"
#include "menuentry.h"
#include "menu.h"
#include "tutorialaction.h"
#include "btfunctions.h"
#include "bashcommandline.h"

using namespace std;

int main(int argc, char **argv)
{
	//cout << "Hello BashTutorial" << endl;

	//[>TutorialAction action("e echo hello > testfile.txt");
	//char* currentDir = (char*) malloc(100);
	//cout << getcwd(currentDir, 100) << endl;
	//action.execute();
	//cout << getcwd(currentDir, 100) << endl;
	//free(currentDir);*/


	////Tutorial tut;
	////tut.loadFromFile("tutorial.tut");
	////tut.execute();
	////cout << tut.execute() << endl;

	//BashTutorial tut("/home/jason/git/ComputerScienceIA/build");
	//SubMenu* parent;
	//Tutorial* st = tut.selectTutorialMenu(parent);
	////cout << parent->getName() << endl;
	//if (st) {
		//tut.executeTutorialFromEntry(st, parent);
		////st->execute();
	//}

	////BashCommandLine b;
	////cout << b.getBashInput() << endl;

	////string tester = "\"\\\"a\n \"";
	////cout << tester.length() << endl;
	////string quote;
	////int pos = findQuoted(tester, quote);
	////cout << quote << endl;

	////BashCommandLine b;
	////b.getBashInputExpected("a", "wrong", "hint");



	//[>BashTutorial bashTutorial;
	//Tutorial testTutorial;
	//bashTutorial.getAvailableTutorials().push_back(&testTutorial);
	//Tutorial* selectedTutorial = bashTutorial.selectTutorialMenu();
	//cout << selectedTutorial->getName() << endl;*/

	BashTutorial tutorial;
	tutorial.startBashTutorial();
}
