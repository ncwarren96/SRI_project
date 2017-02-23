#ifndef INFOBASE_H_
#define INFOBASE_H_
#include "common.h"
class InfoBase{
	public:
		// Constructors and Destructors ------------------------------
		InfoBase();
		~InfoBase();
		// Access Functions ------------------------------------------
		virtual vector<string> lookup(string name);
		virtual boolean check(string name);
		// Manipulation Functions ------------------------------------
		virtual void add(string name, vector<string> targets);
		virtual void remove(string name);
};
#endif