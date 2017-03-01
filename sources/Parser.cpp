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

map<string, vector<string>> Parser::processRule(string p_string){
	stringstream newStream(p_string);
	map<string, vector<string>> rule;
	string first, operand, vars, rest, param;

	getline(newStream, first, ':');
	vector<string> base = parseRule(first);
	rule["name"].push_back(base[0]);
	for(int i=1; i<base.size(); i++){
		rule["vars"].push_back(base[i]);
	}

	getline(newStream, rest, ' ');
	getline(newStream, operand, ' ');
	rule["operand"].push_back(operand);

	int i=1;
	while(getline(newStream, param, ' ')){
		string target = "target";
		target += to_string(i);
		rule[target] = parseRule(param);
		rule["ts"].push_back("");
		i++;
	}

	return rule;
}

vector<string> Parser::parseRule(string p_string){
	vector<string> ret;
	string name, params, var;
	stringstream newStream(p_string);
	getline(newStream, name, '(');
	ret.push_back(name);
	getline(newStream, params, ')');
	stringstream iss(params);
	while(getline(iss, var, ',')){
		ret.push_back(var);
	}
	return ret;
}

vector<string> Parser::processInference(string p_string){
	vector<string> ret = parseRule(p_string);
	return ret;
}