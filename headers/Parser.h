#include "common.h"

class Parser{
	private:
		vector<string> lines;

	public:
		Parser();
		~Parser();
		void addLine(stringstream & p_ss);
		void printLines();

		vector<string> processFact(string p_string);
		vector<string> processRule(string p_string);
		vector<string> processDump(string p_string);
		vector<string> processInference(string p_string);
		vector<string> processDrop(string p_string);
};

