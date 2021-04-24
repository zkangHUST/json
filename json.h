#pragma once
#include<string>
#include<map>
#include<vector>

enum class Type
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
    typedef std::vector<Value>::size_type index;
	Value() :type(Type::Object) {}
    Value(int64_t value) :type(Type::Num), value_num(value) {}
	Value(const std::string& value) :type(Type::String), value_string(value) {}
	Value(const char* str) : type(Type::String), value_string(str) {}
	Value(Type t) :type(t) {}
    
    Value(const Value& that);
    Value(Value&& that);
    Value& operator=(const Value& that);
    Value& operator=(Value&& that);
	Value& operator[](const std::string& key);
    Value& operator[](index i);
    index size() {return value_array.size();}

	bool insert(const std::string& key, const Value& value);
    Value get(const std::string& key) const;
    
	bool isString() const { return type == Type::String; }
	bool isInt() const { return type == Type::Num; }
	bool isBool() const { return type == Type::Bool; }
	bool isArray() const { return type == Type::Array; }
	bool isObject() const { return type == Type::Object; }
	bool isNull() const { return type == Type::Null; }

	std::string asString() const { return value_string; }
	int64_t asInt() const { return value_num; }
	bool asBool() const { return value_bool; }
    
    std::string prettyString() const;
	std::string String() const;
	
    void append(const Value& val);
	void append(Value&& val);
private:
    std::string getObjectStr() const;
    std::string getArrayStr() const;
private:
	Type	        type;
	int64_t		    value_num;
	bool	        value_bool;
    std::string     value_string;
	std::map<std::string, Value> values;
	std::vector<Value> value_array;
};
