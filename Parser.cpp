#include "Parser.h"
#include<iostream>

int Parser::ParseObject(int i, Value& val)
{
    if (i < 0) return i;
	auto status = State::None;
	std::string key;
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
				i = ParseObject(i, sub);
				val[key] = std::move(sub);
            } else {
                return -1;
            }
		} 
		break;
        case TokenType::Array_B:
        {
            if (status == State::Colon) {
                Value array;
                i = ParseArray(i, array);
                val[key] = std::move(array);
            }  else {
                return -1;
            }
        }
        break;
		case  TokenType::Str:
		{
			if (status == State::Colon) {
				auto v = tokens[i].value.substr(1, tokens[i].value.length() - 2);
				val[key] = v;
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
				val[key] = v;
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

int Parser::ParseArray(int i, Value& val)
{
	auto status = State::None;
	std::string key;
	auto flag = true;
	while (i < tokens.size() && flag) {
		switch (tokens[i].type)
		{
		case TokenType::Array_B:
		{
            if (status == State::None) {
                status = State::Array_B;
                i++;
            } else if (status == State::Colon) {
                //
            }
		}
        break;
        case TokenType::Object_B:
            {
                Value obj;
                i = ParseObject(i, obj);
                val.append(std::move(obj));
            }
        break;
        case TokenType::Str:
            {
                if (status == State::Comma ||status == State::Array_B) {
                    auto v = tokens[i].value.substr(1, tokens[i].value.length() - 2);
                    val.append(Value(v));
                }
                i++;
            }
        break;
        case TokenType::Comma:
            {
                status = State::Comma;
                i++;
            }
        break;
        case TokenType::Array_E:
            {
                flag = false;
                break;
            }
        default:
                flag = false;
                break;
        }
    }
	return i + 1;
}

bool Parser::Parse(Value& val)
{
    if (tokens.empty()) return false;
    if (tokens[0].type == TokenType::Object_B) {
        ParseObject(0, val);
    } else if (tokens[0].type == TokenType::Array_B) {
        ParseArray(0, val);
    }
    
    return true;
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
        else if (c == '{' || c == '}' || c == ':' || c == ',' || c == '[' || c == ']') {
			TokenType t = TokenType::Null;
			switch (c)
			{
			case '{': t = TokenType::Object_B; break;
			case '}': t = TokenType::Object_E; break;
			case ':': t = TokenType::Colon; break;
			case ',': t = TokenType::Comma; break;
            case '[': t = TokenType::Array_B;break;
            case ']': t = TokenType::Array_E;break;
			}
			tokens.push_back({t, {1, c}});
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
