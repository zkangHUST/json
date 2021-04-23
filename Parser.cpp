#include "Parser.h"
#include<iostream>

int Parser::PasreObject(int i, Value& val)
{
	auto status = State::None;
	string key;
	auto flag = true;
	while (i < tokens.size() && flag) {
		switch (tokens[i].type)
		{
		case TokenType::Object_B:
		{
			if (status == State::None) {
				status = State::Object_B;
				i++;
			}
			else if (status == State::Colon) {
				Value sub;
				i = PasreObject(i, sub);
				val[key] = sub;
			}
		} 
		break;
		case  TokenType::Str:
		{
			if (status == State::Colon) {
				auto v = tokens[i].value.substr(1, tokens[i].value.length() - 2);
				Value value(v);
				val[key] = value;
				i++;
			}
			else if (status == State::Object_B || status == State::Comma) {
				key = tokens[i].value.substr(1, tokens[i].value.length() - 2);
				i++;
			}
		} 
		break;
		case TokenType::Num:
		{
			if (status == State::Colon) {
				auto v = strtoll(tokens[i].value.c_str(), NULL, 10);
				Value value(v);
				val[key] = value;
				i++;
			}
		}
		break;
		case TokenType::Colon:
		{
			status = State::Colon;
			i++;
		}
		break;
		case TokenType::Comma:
		{
			status = State::Comma;
			i++;
		}
		break;
		case TokenType::Object_E:
			flag = false;
			break;
		default:
			flag = false;
			break;
		}
	}
	return i + 1;
}

int Parser::PasreArray(int i, Value& val)
{
	auto status = State::None;
	string key;
	auto flag = true;
	while (i < tokens.size() && flag) {
		switch (tokens[i].type)
		{
		case TokenType::Array_B:
		{

		}
		{
			if (status == State::None) {
				status = State::Object_B;
				i++;
			}
			else if (status == State::Colon) {
				Value sub;
				i = PasreObject(i, sub);
				val[key] = sub;
			}
		}
		break;
		case  TokenType::Str:
		{
			if (status == State::Colon) {
				auto v = tokens[i].value.substr(1, tokens[i].value.length() - 2);
				Value value(v);
				val[key] = value;
				i++;
			}
			else if (status == State::Object_B || status == State::Comma) {
				key = tokens[i].value.substr(1, tokens[i].value.length() - 2);
				i++;
			}
		}
		break;
		case TokenType::Num:
		{
			if (status == State::Colon) {
				auto v = strtoll(tokens[i].value.c_str(), NULL, 10);
				Value value(v);
				val[key] = value;
				i++;
			}
		}
		break;
		case TokenType::Colon:
		{
			status = State::Colon;
			i++;
		}
		break;
		case TokenType::Comma:
		{
			status = State::Comma;
			i++;
		}
		break;
		case TokenType::Object_E:
			flag = false;
			break;
		default:
			flag = false;
			break;
		}
	}
	return i + 1;
}

void Parser::printTokens()
{
	for (auto& it : tokens) {
		std::cout << it.value << std::endl;
	}
}

bool Parser::Tokenize()
{
	auto i = 0;
	while (i < input.size()) {
		auto c = input[i];
		if (isspace(c)) {
			i++;
		}
		else if (c == '{' || c == '}' || c == ':' || c == ',') {
			string tmp(1, c);
			TokenType t;
			switch (c)
			{
			case '{': t = TokenType::Object_B; break;
			case '}': t = TokenType::Object_E; break;
			case ':': t = TokenType::Colon; break;
			case ',': t = TokenType::Comma; break;
			default:break;
			}
			tokens.push_back({t, tmp });
			i++;
		}
		else if (c == '\"') {
			auto start = i;
			i++;
			while (input[i++] != '\"');
			auto token = input.substr(start, i - start);
			tokens.push_back({TokenType::Str, token});
		}
		else if (c >= '0' && c <= '9') {
			auto start = i;
			while (input[i] >= '0' && input[i] <= '9') i++;
			auto token = input.substr(start, i - start);
			tokens.push_back({ TokenType::Num, token });
		}
		else if (c == 't') {
			auto token = input.substr(i, 4);
			if (token == "true") {
				tokens.push_back({ TokenType::Bool, token });
			}
			i += 4;
		}
		else if (c == 'f') {
			auto token = input.substr(i, 5);
			if (token == "false") {
				tokens.push_back({ TokenType::Bool, token });
			}
			i += 5;
		}
		else {
			return false;
		}
	}
	return true;
}

string Parser::getNextToken()
{
	auto start = i;
	string token;
	while (i < input.size())
	{
		auto c = input[i];
		if (isspace(c)) {
			i++;
			start = i;
		}
		else if (c == '{' || c == '}' || c == ',') {
			token = c;
			i++;
			break;
		}else if (c == ':') {
			token = c;
			i++;
			break;
		}
		else if (c == '\"') {
			i++;
			while (i < input.size() && input[i] != '\"') {
				i++;
			}
			i++;
			token = input.substr(start, i - start);
			break;
		}
		else if (c >= '0' && c <= '9') {
			while (i < input.size() && input[i] >= '0' && input[i] <= '9') {
				i++;
			}
			token = input.substr(start, i - start);
			start = i;
			break;
		}
	}
	return token;
}