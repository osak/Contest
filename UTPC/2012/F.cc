#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    long long A, B;
    cin >> A >> B;

    srand(time(NULL));
    map<long long,vector<string> > m;
    for(int times = 0; times < 10000; ++times) {
        long long hash = 0;
        string str;
        for(int i = 0; i < 50; ++i) {
            int val = rand() % 26 + 1;
            str += (val-1)+'a';
            hash *= A;
            hash += val;
            hash %= B;
            m[hash].push_back(str);
        }
    }

    int maxhash = 0;
    int maxsize = 0;
    for(map<long long,vector<string> >::const_iterator it = m.begin(); it != m.end(); ++it) {
        if((int)m.size() > maxsize) {
            maxhash = it->first;
            maxsize = m.size();
        }
    }
    vector<string> &v = m[maxhash];
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int cnt = 0;
    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl;
        if(++cnt == 100) break;
    }
    return 0;
}
