#include "common.h"

class Parser{
	private:
		typedef void (Parser::*ParserMFP)(string);
		map<string, ParserMFP> funcMap;
		vector<string> lines;

	public:
		Parser();
		~Parser();
		void addLine(stringstream & p_ss);
		void printLines();

		void processLine(stringstream & p_ss);
		void processFact(string p_string);
		void processRule(string p_string);
		void processLoad(string p_string);
		void processDump(string p_string);
		void processInference(string p_string);
		void processDrop(string p_string);
};

