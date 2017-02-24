#include "Parser.h"

Parser::Parser(){
	funcMap.insert(make_pair("FACT", &Parser::processFact));
	funcMap.insert(make_pair("RULE", &Parser::processRule));
	funcMap.insert(make_pair("LOAD", &Parser::processLoad));
	funcMap.insert(make_pair("DUMP", &Parser::processDump));
	funcMap.insert(make_pair("INFERENCE", &Parser::processInference));
	funcMap.insert(make_pair("DROP", &Parser::processDrop));
}

Parser::~Parser(){
	cout<<"destructing Parser\n";
}

void Parser::addLine(stringstream & p_ss){
	string line = "";
	getline(p_ss,line,'#');
	lines.push_back(line);
}

void Parser::printLines(){
	for(int i=0; i<lines.size(); i++){
		cout<<lines[i]<<endl;
	}
}

void Parser::processLine(stringstream & p_ss){
	string action = "";
	string body = "";
	getline(p_ss,action,' ');
	getline(p_ss,body, '#');
	ParserMFP func = funcMap[action];
	return (this->*func)(body);
}

void Parser::processFact(string p_string){
	stringstream newStream(p_string);
	vector<string> params;
	string relationship = "";
	string rest = "";

	getline(newStream, relationship,'(');
	getline(newStream, rest, ')');
	stringstream newerStream(rest);
	while(getline(newerStream, rest, ',')){
		params.push_back(rest);
	}
}

void Parser::processRule(string p_string){
	stringstream newStream(p_string);
	vector<string> params;
	string rule = "";
	string operand = "";
	string rest = "";

	getline(newStream, rule, ':');
	getline(newStream, rest, ' ');
	getline(newStream, operand, ' ');
	while(getline(newStream, rest, ' ')){
		params.push_back(rest);
	}
}

void Parser::processLoad(string p_string){
	ifstream readFile(p_string);
	string line = "";
	while(getline(readFile,line)){
		stringstream newStream(line);
		stringstream newStream1(line);
		this->addLine(newStream);
		this->processLine(newStream1);
	}
}

void Parser::processDump(string p_string){
	//cout<<"Parsing dump: "<<p_string<<endl;
}

void Parser::processInference(string p_string){
	//cout<<"Parsing inference: "<<p_string<<endl;
}

void Parser::processDrop(string p_string){
	//cout<<"Parsing drop: "<<p_string<<endl;
}