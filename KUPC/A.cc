#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    map<char, int> m;
    for(int i = 0; i < s.size(); ++i)
        m[s[i]]++;
    cout << min(m['K'], min(m['U'], min(m['P'], m['C']))) << endl;

    return 0;
}
