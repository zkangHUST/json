//
//  test.cpp
//  myjson
//
//  Created by vincent.zheng on 2021/4/23.
//

#include "test.hpp"
#include <iostream>
using namespace std;
#define LOG(x)   cout <<__TIME__ << ":" << __FUNCTION__ <<":" << x << endl;
void TEST()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test10();
}
void test1()
{
    Value root, a,b;
    a["name"] = "trump";
    a["age"] = int64_t(50);
    b["name"] = "vincent";
    b["role"] = "ceo";
    root.append(std::move(a));
    root.append(std::move(b));
    auto s = root.String();
    Parser p(s);
    p.Tokenize();
    Value val;
    p.Parse(val);
//    LOG(p.prettyJson());
//    LOG(s);
    if (s != val.String()) {
        std::cout << "TEST1 fail" << std::endl;
    } else {
        std::cout << "TEST1 Pass" << std::endl;
    }
    LOG(val.prettyString());
}

void test2()
{
    Value trump, slogan;
    trump["name"] = "trump";
    trump["job"] = "president";
    trump["rich"] = bool(true);
    slogan.append("you are fired!");
    slogan.append("fake news");
    trump["slogn"] = slogan;
    auto s = trump.String();
    LOG(s);
    Parser p(s);
    p.Tokenize();
    Value val;
    p.Parse(val);
//    LOG(p.prettyJson());
//    std::cout << s << std::endl;
    auto pass = true;
    if (s != val.String()) {
        std::cout << "TEST2 fail" << std::endl;
        std::cout << s << std::endl;
        std::cout << val.String() << std::endl;
        pass = false;
    }
    auto name = val.get("name").asString();
    if (name != "trump"){
        std::cout << "TEST2 fail" << std::endl;
        std::cout << name << std::endl;
        pass = false;
    }
    auto job = val.get("job");
//    LOG(job.asString());

    if (job.asString() != "president") {
        pass = false;
        LOG(job.asString());
    }
    
    auto rich = val.get("rich");
    if (rich.asInt() != 1) {
        LOG(rich.asInt());
    }
    
    auto slogn = val.get("slogan");
    if (!slogan.isArray()) {
        pass = false;
        LOG("slogn not array");
    }
    if (slogan[0].asString() != "you are fired!") {
        pass = false;
        LOG(slogan[0].asString());
    }
    if (slogan[1].asString() != "fake news") {
        pass = false;
        LOG(slogan[1].asString());
    }
    if (pass) {
        cout << "TEST2 Pass" << endl;
    }
    LOG(val.prettyString());
}

void test3()
{
    Value root;
    root["boss"]["name"].append("fangxing");
    root["boss"]["name"].append("vincent");
    root["age"] = 12;
    auto s = root.String();
    Parser p(s);
    p.Tokenize();
    Value val;
    p.Parse(val);
    if (s != val.String()) {
        LOG(s);
    } else {
        LOG("pass");
    }
    LOG(val.prettyString());
}


void test4()
{
    Value root, a,b;
    a["name"].append("trump");
    a["name"].append("vicnent");
    a["age"] = int64_t(50);
    b["name"] = "vincent";
    b["role"] = "ceo";
    root.append(std::move(a));
    root.append(std::move(b));
    auto s = root.String();
    Parser p(s);
    p.Tokenize();
    Value val;
    p.Parse(val);
//    LOG(p.prettyJson());
//    LOG(s);
    if (s != val.String()) {
        std::cout << "TEST1 fail" << std::endl;
    } else {
        std::cout << "TEST1 Pass" << std::endl;
    }
    LOG(val.prettyString());
}

void test5()
{
    Value root;
    Value item;
    item.append("trump");
    item.append("vincent");
    root.append(item);
    root.append(item);
    auto s = root.String();
    Value val;
    Parser p(s);
    p.Tokenize();
    p.Parse(val);
    LOG(val.prettyString());
}

void test6()
{
    Value root;
    Value item;
    root["a"]["b"] = "c";
    root["a"]["c"] = "e";
//    item.append("vincent");
//    root.append(item);
//    root.append(item);
    auto s = root.String();
    Value val;
    Parser p(s);
    p.Tokenize();
    p.Parse(val);
    LOG(val.prettyString());
}

static void baseTest(const std::string& str)
{
    Parser p(str);
    p.Tokenize();
    Value val;
    p.Parse(val);
    LOG(val.prettyString());
}

void test10()
{
    std::vector<std::string> vec;
    std::string s;
    while(cin>>s) {
        vec.push_back(s);
    }
    for (auto it:vec) {
        baseTest(it);
    }
}

