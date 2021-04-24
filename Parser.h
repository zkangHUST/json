#pragma once
#include<string>
#include<vector>
#include "json.h"

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
	Token(TokenType t, const std::string& val):type(t), value(val) {}
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
    Parser(){};
	Parser(const std::string& in) :input(in){};
	bool Tokenize();
	void printTokens();
    bool Parse(Value& val);

private:
    int ParseObject(int i, Value& val);
	int ParseArray(int i, Value& val);
	int ParseString(int i, Value& val);
	int ParseNum(int i, Value& val);

private:
	std::vector<Token> tokens;
    std::string input;
};
