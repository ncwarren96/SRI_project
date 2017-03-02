#include "common.h"

class Parser{
	private:
		vector<string> lines;

	public:
		// Constructors and Destructors ----------------------------------------------
		Parser();
		~Parser();
		
		// Input and Output ----------------------------------------------------------
		void addLine(stringstream & p_ss); // adds new line to lines
		void printLines();	// prints lines
	
		// Processing Methods --------------------------------------------------------
		vector<string> processFact(string p_string); // parses a fact
		map<string, vector<string>> processRule(string p_string); // processes a rule from a string to add to the rule base
		vector<string> parseRule(string p_string); // parses a rule
		vector<string> processInference(string p_string); // parses the inference command
		
};

