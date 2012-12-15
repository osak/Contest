//Name: AT - sequence
//Level: 1
//Category: 文字列,やるだけ
//Note:

/*
 * 与えられる文字列はcorrectであることが保障されているのでやるだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string line;
    cin >> line;
    int pos = 2;
    const int len = line.size();
    while(pos < len) {
        int start = pos;
        if(pos < len && isupper(line[pos])) {
            ++pos;
            if(pos < len && isupper(line[pos])) ++pos;
        } else if(pos < len) {
            // it must be symbol
            ++pos;
            if(pos < len && isupper(line[pos])) ++pos;
        }
        while(pos < len && isdigit(line[pos])) ++pos;
        if(pos < len && line[pos] == '=') {
            ++pos;
            while(pos < len && isdigit(line[pos])) ++pos;
        }
        cout << line.substr(start, pos-start) << endl;
    }
    return 0;
}
