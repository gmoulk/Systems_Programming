#include <iostream>
#include <iterator>
#include <map>
using namespace std;

typedef struct {
    string name;
    int app;
} insert_str;

int main(void){
    map<string, insert_str> test;
    insert_str test_s[4];

    test_s[0].app = 1;
    test_s[0].name = "1";
    test_s[1].app = 1;
    test_s[1].name = "2";
    test_s[2].app = 1;
    test_s[2].name = "1";
    test_s[3].app = 1;
    test_s[3].name = "3";

    test.insert(std::pair<string,insert_str>("1",test_s[0]));
    test.insert(std::pair<string,insert_str>("2",test_s[1]));
    test.insert(std::pair<string,insert_str>("3",test_s[3]));

    // for (auto itr = test.find("1"); itr != test.end(); itr++) {
       
    //     cout << itr->first << '\t' << itr->second.app << itr->second.name << '\n';
    // }

    for (auto itr = test.begin(); itr != test.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second.app << '\t' << itr->second.name
             << '\n';
    }
    auto itr = test.begin();
    if((itr = test.find("1")) != test.end()){
        itr->second.app++;
    }
    cout << "###################################################"<< endl;
    for (auto itr = test.begin(); itr != test.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second.app << '\t' << itr->second.name
             << '\n';
    }
}