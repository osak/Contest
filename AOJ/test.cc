#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    string str = "ab";
    int i = 0;
    cout << str.substr(1, 0) << endl;
    string ans = str.substr(0, i) + str.substr(i+1, 1-(i+1)) + str.substr(1+1);
    cout << ans << endl;


    printf("%.3f\n", 1.2346);
    return 0;
}
