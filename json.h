#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;

enum Type
{
	Null = 0,
	String,
	Num,
	Bool,
	Object,
	Array,
};

class Value{
public:
	Value() :type(Type::Object) {}
	Value(int64_t value) :type(Type::Num), value_num(value) {}
	Value(const string& value) :type(Type::String), value_string(value) {}
	Value(const char* str) : type(Type::String), value_string(str) {}
	Value(Type t) :type(t) {}
	//Value& operator=(const Value& other);
	Value& operator[](const string& key);

	bool insert(const string& key, const Value& value);
	Value get(const string& key) const;
	bool isString() const { return type == Type::String; }
	bool isInt() const { return type == Num; }
	bool isBool() const { return type == Bool; }
	bool isArray() const { return type == Array; }
	bool isObject() const { return type == Object; }
	bool isNull() const { return type == Null; }

	string asString() const { return value_string; }
	int asInt() const { return value_num; }
	bool asBool() const { return value_bool; }

	bool getNextToken(const string& input, string& token);
	string String() const;
	void setType(Type t) { type = t; }
	void setVal(const string& val) { value_string = val; }
	void setVal(int val) { value_num = val; }
	void append(const Value& val);// { value_array.push_back(val); }
	void append(Value&& val);// { value_array.push_back(val); }
private:
	Type	type;
	//string	key;
	string	value_string;
	int64_t		value_num;
	bool	value_bool;
	map<string, Value> values;
	std::vector<Value> value_array;
};