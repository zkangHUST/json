#pragma once
#include<string>
#include "json.h"
#include<vector>



struct item {
	Value value;
	item* next;
	item* child;
	item* father;
};

enum struct TokenType {
	Null = 0,
	Str,
	Num,
	Bool,
	Object_B,
	Object_E,
	Comma,
	Colon,
	Array_B,
	Array_E,
};

struct Token {
	Token():type(TokenType::Null) {}
	Token(TokenType t, const string& val):type(t), value(val) {}
	TokenType type;
	std::string value;
};


enum class State {
	None,
	Object_B,
	Object_E,
	Array_B,
	Array_E,
	Colon,
	Comma,
	Key,
	value,
};
class Parser {
public:
	Parser() :i(0) {};
	Parser(const string& in) :input(in), i(0) {};
	bool Tokenize();
	void printTokens();
	string getNextToken();
	int PasreObject(int i, Value& val);
	int PasreArray(int i, Value& val);
	int ParseString(int i, Value& val);
	int ParseNum(int i, Value& val);
private:

private:
	//std::vector<string> tokens_;
	std::vector<Token> tokens;
	string perToken;
	string input;
	int i;
	item* root;
};
