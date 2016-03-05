#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <string>

using namespace std;

class MenuEntry
{
	private:
		//the name of the menuentry
		string name;
		//the description of the menuentry
		string description;

	public:
		MenuEntry(const string& name, const string& description);
		MenuEntry();

		virtual string getEntryLine() const;

		//getters and setters for main variables
		string getName() const;
		void setName(const string& name);
		string getDescription() const;
		void setDescription(const string &description);

		virtual bool isMenuEntry() const;
		//returns opposite of above for convenience, isn't meant to be overridden
		bool isItemEntry() const;
};

#endif
