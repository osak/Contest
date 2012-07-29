//Name: String
//Level: 2
//Category: 文字列,シミュレーション
//Note:

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        string str;
        cin >> str;
        while(N--) {
            string tmp;
            ostringstream ss(tmp);

            int pos = 0;
            while(pos < str.size()) {
                int start = pos;
                char c = str[pos];
                while(pos < str.size() && str[pos] == c) ++pos;
                ss << (pos-start) << c;
            }
            str = ss.str();
        }
        cout << str << endl;
    }
    return 0;
}

