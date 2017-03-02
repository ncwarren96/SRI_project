#include "common.h"
#include "InfoBase.h"

class KnowledgeBase: public InfoBase{
	private:
		map< string, vector< vector<string> > > fact_map;
	public:
		// Constructors and Destructors -------------------------------------------------------
		KnowledgeBase();
		~KnowledgeBase();

		// Access Functions -------------------------------------------------------------------
		vector< vector<string> > lookup(string name);	// returns the vector mapped at "name"
		bool check(string name);			// true if fact with key "name" exists
		int numFacts();	// returns number of facts in the Knowledge Base
	
		// Manipulation Functions --------------------------------------------------------------
		void add(vector<string> data);	// creates new fact with key "name" or appends targets to vector if "name" already mapped
		void removeAll(string name);	// deletes ENTIRE entry with key "name"
		void remove(vector<string> data);	// delete specific fact, where data.begin = name of fact

		vector<vector<string>> getFacts();	// returns all facts in the Knowledge Base
};