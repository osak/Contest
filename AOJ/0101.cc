//Name: Aizu PR
//Level: 1
//Category: 文字列,String,やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    cin.ignore();
    for(int i = 0; i < N; ++i) {
        string str;
        getline(cin, str);
        while(true) {
            size_t pos = str.find("Hoshino");
            if(pos == string::npos) break;
            str = str.substr(0, pos) + "Hoshina" + str.substr(pos + 7);
        }
        cout << str << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
