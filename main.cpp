#include<iostream>
//#include "minStack.hpp"
#include"json.h"
#include "Parser.h"
#include "test.hpp"
using namespace std;
int main(int argc, char* agrv[])
{
    cout << argc << endl;
    if (argc <= 1) {
        test8();
    } else {
        test10();
    }
//    TEST();
    return 0;
}
