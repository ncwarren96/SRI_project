#include "Parser.h"

Parser::Parser(){
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

vector<string> Parser::processFact(string p_string){
	stringstream newStream(p_string);
	vector<string> params;
	string relationship = "";
	string rest = "";

	getline(newStream, relationship,'(');
	getline(newStream, rest, ')');
	stringstream newerStream(rest);
	
	params.push_back(relationship);
	while(getline(newerStream, rest, ',')){
		params.push_back(rest);
	}
	return params;
}

vector<string> Parser::processRule(string p_string){
	stringstream newStream(p_string);
	vector<string> params;
	string rule = "";
	string operand = "";
	string rest = "";

	getline(newStream, rule, ':');
	getline(newStream, rest, ' ');
	getline(newStream, operand, ' ');
	
	params.push_back(rule);
	params.push_back(operand);
	while(getline(newStream, rest, ' ')){
		params.push_back(rest);
	}
	return params;
}

vector<string> Parser::processInference(string p_string){
	vector<string> ret;
	string th;
	stringstream newStream(p_string);
	while(getline(newStream, th, ' ')){
		ret.push_back(th);
	}
	return ret;
}