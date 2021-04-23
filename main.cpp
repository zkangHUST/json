#include<iostream>
//#include "minStack.hpp"
#include"json.h"
#include "Parser.h"
using namespace std;
int main()
{
	Value root;

	//root["person"]["name"] = "vincent";
	root["person"]["age"] = 18;
	//root["name"]["boss"] = "vincent";
	root["salary"] = 10000000;
	root["name"].append("vincent");
	root["name"].append("trump");

	auto s = root.String();
	cout << s;
	auto p = Parser(s);
	p.Tokenize();
	//p.printTokens();
	Value v;
	p.PasreObject(0, v);

	cout << v.String(); 
	return 0;
}