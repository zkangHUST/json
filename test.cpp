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
    test7();
    test8();
    test9();
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


void test7()
{
    std::string str = "{\"status\":\"0000\",\"message\":\"success\",\"data\":{\"title\":{\"id\":\"001\",\"name\":\"白菜\"},\"content\":[{\"id\":\"001\",\"value\":\"你好白菜\"},{\"id\":\"002\",\"value\":\"你好萝卜\"}]}}";
    Parser p(str);
    p.Tokenize();
    Value val;
    p.Parse(val);
    LOG(val.prettyString());
}


void test8()
{
    std::string str = "{\"animal\":\"cat\",\"color\":\"orange\"}";
    Parser p(str);
    p.Tokenize();
    Value val;
    p.Parse(val);
    LOG(val.prettyString());
}

void test9()
{
    std::string str = "{\"name\":\"Flutty\",\"breed\":\"Siamese\",\"age\":2}";
    Parser p(str);
    p.Tokenize();
    Value val;
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
    std::vector<std::string> strs = {
        "{\"person\":{\"name\":\"LindsayBassett\",\"heightInInches\":66,\"head\":{\"hair\":{\"color\":\"lightblood\",\"length\":\"short\",\"style\":\"a-line\"},\"eyes\":\"green\"}}}",
        "{\"eggCartoon\":[\"egg\",\"egg\",\"egg\",\"egg\",\"egg\",\"egg\",\"egg\",null,\"egg\",null,\"egg\",]}",
        "{\"students\":[\"张三\",\"李四\",\"王五\",\"赵六\",\"孙琪\",\"钱吧\"]}",
        "{\"scores\":[128,113,105,120,100]}",
        "{\"employees\":[{\"firstName\":\"Bill\",\"lastName\":\"Gates\"},{\"firstName\":\"George\",\"lastName\":\"Bush\"},{\"firstName\":\"Thomas\",\"lastName\":\"Carter\"}]}",
        "{\"name\":\"username\",\"age\":20,\"admin\":true}",
        "{\"HeWeather6\":[{\"basic\":{\"cid\":\"CN101010100\",\"location\":\"北京\",\"parent_city\":\"北京\",\"admin_area\":\"北京\",\"cnty\":\"中国\",\"lat\":\"39.90498734\",\"lon\":\"116.40528870\",\"tz\":\"8.0\"},\"daily_forecast\":[{\"cond_code_d\":\"103\",\"cond_code_n\":\"101\",\"cond_txt_d\":\"晴间多云\",\"cond_txt_n\":\"多云\",\"date\":\"2017-10-26\",\"hum\":\"57\",\"pcpn\":\"0.0\",\"pop\":\"0\",\"pres\":\"1020\",\"tmp_max\":\"16\",\"tmp_min\":\"8\",\"uv_index\":\"3\",\"vis\":\"16\",\"wind_deg\":\"0\",\"wind_dir\":\"无持续风向\",\"wind_sc\":\"微风\",\"wind_spd\":\"5\"},{\"cond_code_d\":\"101\",\"cond_code_n\":\"501\",\"cond_txt_d\":\"多云\",\"cond_txt_n\":\"雾\",\"date\":\"2017-10-27\",\"hum\":\"56\",\"pcpn\":\"0.0\",\"pop\":\"0\",\"pres\":\"1018\",\"tmp_max\":\"18\",\"tmp_min\":\"9\",\"uv_index\":\"3\",\"vis\":\"20\",\"wind_deg\":\"187\",\"wind_dir\":\"南风\",\"wind_sc\":\"微风\",\"wind_spd\":\"6\"},{\"cond_code_d\":\"101\",\"cond_code_n\":\"101\",\"cond_txt_d\":\"多云\",\"cond_txt_n\":\"多云\",\"date\":\"2017-10-28\",\"hum\":\"26\",\"pcpn\":\"0.0\",\"pop\":\"0\",\"pres\":\"1029\",\"tmp_max\":\"17\",\"tmp_min\":\"5\",\"uv_index\":\"2\",\"vis\":\"20\",\"wind_deg\":\"2\",\"wind_dir\":\"北风\",\"wind_sc\":\"3-4\",\"wind_spd\":\"19\"}],\"status\":\"ok\",\"update\":{\"loc\":\"2017-10-2623:09\",\"utc\":\"2017-10-2615:09\"}}]}",
        "{\"data\":[{\"deliveryListId\":\"20180001\",\"shipperCode\":\"0030\",\"shortShipperName\":\"RB\",\"orderNo\":\"102018032001\",\"deliveryOrder\":1,\"receiverName\":\"吉田XXX\",\"receiverTelNo\":\"07012340303\",\"receiverAddress1\":\"東京都足立区足立1-1\",\"receiverAddress2\":\"東京都足立区足立1-2\",\"isCod\":true,\"billAmount\":5,\"geocodingScore\":50,\"latitudeJP\":\"56789.33\",\"longitudeJP\":\"123456.33\",\"latitude\":\"20180001.22\",\"longitude\":\"20180001.33\",\"vehicleId\":\"239\",\"orderDetails\":[{\"trackingNo\":\"201803200001\",\"quantity\":1,\"lapCount\":null,\"statusCode\":null,\"statusNameMobile\":null},{\"trackingNo\":\"201803200002\",\"quantity\":1,\"lapCount\":4,\"statusCode\":\"100\",\"statusNameMobile\":\"配送準備中\"},{\"trackingNo\":\"201803200003\",\"quantity\":1,\"lapCount\":4,\"statusCode\":\"300\",\"statusNameMobile\":\"持出し\"},{\"trackingNo\":\"201803200004\",\"quantity\":1,\"lapCount\":4,\"statusCode\":\"100\",\"statusNameMobile\":\"配送準備中\"},{\"trackingNo\":\"201803200005\",\"quantity\":1,\"lapCount\":4,\"statusCode\":\"100\",\"statusNameMobile\":\"配送準備中\"}]}]}"
    };
    for(auto it:strs) {
        baseTest(it);
    }
}


void test11()
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

