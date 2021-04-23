#include "json.h"


bool Value::insert(const string& key, const Value& value)
{
	values.emplace(key, value);
}

Value Value::get(const string& key) const
{
	auto it = values.find(key);
	if (it != values.end()) {
		return it->second;
	}
	return Value();
}

bool Value::getNextToken(const string& input, string& token)
{
	return false;
}

string Value::String() const
{
	string s;
	if (type == Type::String) {
		return "\"" + value_string + "\"";
	}
	else if (type == Type::Num) {
		return std::to_string(value_num);
	}
	else if (type == Type::Object){
		s = "{";
		for (auto it = values.cbegin(); it != values.cend();++it) {
			auto key = "\"" + it->first + "\"";
			s += key;
			s += ":";
			s += it->second.String();
			if (std::distance(it, values.cend()) > 1) {
				s += ",";
			}
		}
		s += "}";
		return s;
	}
	else if (type == Type::Array) {
		s = "[";
		for (auto it = value_array.cbegin(); it != value_array.cend();it++) {
			s += it->String();
			if (std::distance(it, value_array.end()) > 1) {
				s += ",";
			}
		}
		s += "]";
		return s;
	}
		
	return string();
}

void Value::append(const Value& val)
{
	type = Type::Array;
	value_array.push_back(val);
}

void Value::append(Value&& val)
{
	type = Type::Array;
	value_array.push_back(val);
}

Value& Value::operator[](const string& key)
{
	return values[key];
}
