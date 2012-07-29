//Name: Apple and Peach
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    getline(cin, str);
    size_t pos = 0;
    while((pos=str.find("apple", pos)) != string::npos) {
        str.replace(pos, 5, "_____");
        pos += 5;
    }
    pos = 0;
    while((pos=str.find("peach", pos)) != string::npos) {
        str.replace(pos, 5, "apple");
        pos += 5;
    }
    pos = 0;
    while((pos=str.find("_____", pos)) != string::npos) {
        str.replace(pos, 5, "peach");
        pos += 5;
    }
    cout << str << endl;
    return 0;
}
