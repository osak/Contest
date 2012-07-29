//Name: Trading
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int main() {
    map<int, int> m;
    int n, cnt;
    char comma;

    while(true) {
        string str;
        getline(cin, str);
        if(str == "") break;

        istringstream is(str);
        is >> n >> comma >> cnt;
        m[n]++;
    }

    set<int> s;
    while(cin >> n >> comma >> cnt) {
        if(m.count(n) > 0) {
            m[n]++;
            s.insert(n);
        }
    }

    for(set<int>::iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << ' ' << m[*it] << endl;
    return 0;
}
