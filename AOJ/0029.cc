#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<string, int> freq;
    int modecnt = 0;
    string mode;
    string longest;
    string str;
    while(cin >> str) {
        if(modecnt < ++freq[str]) {
            modecnt = freq[str];
            mode = str;
        }
        if(str.size() > longest.size()) longest = str;
    }
    cout << mode << ' ' << longest << endl;
    return 0;
}
