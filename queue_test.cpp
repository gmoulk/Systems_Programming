#include <iostream>
#include <queue>
#include <iterator>
using namespace std;

typedef struct {
    string name;
    int app;
} insert_str;

int main(void){
    queue<insert_str> test;

    insert_str test_s[4];

    test_s[0].app = 1;
    test_s[0].name = "1";
    test_s[1].app = 1;
    test_s[1].name = "2";
    test_s[2].app = 1;
    test_s[2].name = "1";
    test_s[3].app = 1;
    test_s[3].name = "3";

    test.push(test_s[0]);
    test.push(test_s[1]);
    test.push(test_s[2]);
    test.push(test_s[3]);

     while (!test.empty()) {
        cout << test.front().name << ' ';
        test.pop();
    }
}