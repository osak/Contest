#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

set<unsigned long long> failed;
bool dfs(const vector<int> &v, int pos, unsigned long long used) {
    if(used == (1<<v.size())-1) return true;
    if(failed.count(used)) return false;

    unsigned long long mask = 1;
    for(int i = 0; i < v.size(); ++i, mask <<= 1) {
        if(used & mask) continue;
        if(v[pos] & v[i]) {
            if(dfs(v, pos, used | mask)) return true;
        }
    }

    failed.insert(used);
    return false;
}

int main() {
    int N;
    while(cin >> N) {
        vector<int> v(N, 0);
        for(int i = 0; i < N; ++i) {
            string name, b;
            cin >> name >> b;
            for(int j = 0; j < b.size(); ++j) {
                if(b[j] == 'A') v[i] |= (1<<0);
                else if(b[j] == 'C') v[i] |= (1<<1);
                else if(b[j] == 'G') v[i] |= (1<<2);
            }
        }

        unsigned long long used = 1;
        failed.clear();
        if(dfs(v, 0, used)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}
