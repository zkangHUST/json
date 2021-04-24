#include "json.h"

Value::Value(const Value& that):type(that.type),value_string(that.value_string),value_num(that.value_num),value_bool(that.value_bool),values(that.values),value_array(that.value_array)
{
}

Value::Value(Value&& that):type(that.type),value_num(that.value_num),value_bool(that.value_bool)
{
    value_string = std::move(that.value_string);
    values = std::move(that.values);
    value_array = std::move(that.value_array);
}

Value& Value::operator=(const Value& that)
{
    if (this == &that) {
        return *this;
    }
    type = that.type;
    value_string = that.value_string;
    value_num = that.value_num;
    value_bool = that.value_bool;
    values = that.values;
    value_array = that.value_array;
    return *this;
}

Value& Value::operator=(Value&& that)
{
    if (this == &that) {
        return *this;
    }
    type = that.type;
    value_string = std::move(that.value_string);
    value_num = that.value_num;
    value_bool = that.value_bool;
    values = std::move(that.values);
    value_array = std::move(that.value_array);
    return *this;
    
}

bool Value::insert(const std::string& key, const Value& value)
{
	values.emplace(key, value);
    return true;
}

Value Value::get(const std::string& key) const
{
	auto it = values.find(key);
	if (it != values.end()) {
		return it->second;
	}
	return Value(Type::Null);
}

std::string Value::String() const
{
    switch(type) {
        case Type::Object:
            return getObjectStr();
        case Type::Array:
            return getArrayStr();
        case Type::Bool:
            return value_bool ? "true" : "false";
        case Type::String:
            return "\"" + value_string + "\"";
        case Type::Num:
            return std::to_string(value_num);
        case Type::Null:
            return "null";
    }
	return std::string();
}

std::string Value::getObjectStr() const
{
    if (type != Type::Object || values.empty()) return "";
    std::string s = "{";
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

std::string Value::getArrayStr() const
{
    if (type != Type::Array ||value_array.empty()) return "";
    std::string s = "[";
    for (auto it = value_array.cbegin(); it != value_array.cend();it++) {
        s += it->String();
        if (std::distance(it, value_array.end()) > 1) {
            s += ",";
        }
    }
    s += "]";
    return s;
}

void Value::append(const Value& val)
{
	type = Type::Array;
	value_array.push_back(val);
}

void Value::append(Value&& val)
{
	type = Type::Array;
	value_array.push_back(std::move(val));
}

Value& Value::operator[](const std::string& key)
{
	return values[key];
}

Value& Value::operator[](index i)
{
    assert(i >= 0 || i < value_array.size());
    return value_array[i];
}

std::string blank(int tabNums, bool r = true)
{
    assert(tabNums >= 0);
    return std::string(4 * tabNums, ' ');
}
std::string Value::prettyString() const
{
    auto rawText = String();
    std::string ret = "\n";
    auto level = 0;
    for (auto c : rawText) {
        if (c == '{' || c == '[') {
            ret += c;
            level += 1;
            ret += "\n";
            ret += blank(level);
        } else if (c == '}' || c == ']') {
            level -= 1;
            ret += "\n";
            ret += blank(level);
            ret += c;
        }
        else if (c == ',') {
            ret += c;
            ret += "\n";
            ret += blank(level);
        } else {
            ret += c;
        }
    }
    return ret;
}
