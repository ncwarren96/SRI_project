#ifndef INFOBASE_H_
#define INFOBASE_H_
#include "common.h"
class InfoBase{
	public:
		// Constructors and Destructors ------------------------------
		InfoBase();
		~InfoBase();
		// Access Functions ------------------------------------------
		virtual vector< vector<string> > lookup(string name) = 0;
		virtual bool check(string name) = 0;
		// Manipulation Functions ------------------------------------
		virtual void add(string name, vector<string> targets) = 0;
		virtual void remove(string name) = 0;
};
#endif