#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        vector<int> v(10);
        for(int j = 0; j < 10; ++j) {
            string s;
            cin >> s;
            if(s == "END") return 0;

            int n = 0;
            for(int k = 0; k < 5; ++k) {
                n <<= 1;
                if(s[k] == '1') n |= 1;
            }
            v[j] = n;
        }

        set<vector<int> > used;
        vector<int> s(10);
        int ans = 0;
        for(int i = 5; i < 10; ++i) s[i] = 1;
        do {
            vector<int> v1, v2;
            for(int i = 0; i < 10; ++i) {
                if(s[i]) v1.push_back(v[i]);
                else v2.push_back(v[i]);
            }

            vector<int> ord(5);
            for(int i = 0; i < 5; ++i) ord[i] = i;
            do {
                for(int rev = 0; rev < (1<<5); ++rev) {
                    vector<int> pat(5, 0);
                    for(int r = 0; r < 5; ++r) {
                        for(int c = 0; c < 5; ++c) {
                            int rpos = (rev&(1<<c)) ? r : 4-r;
                            pat[r] <<= 1;
                            pat[r] |= (v1[ord[c]]&(1<<rpos)) ? 1 : 0;
                        }
                    }
                    if(used.count(pat)) continue;
                    bool ok = true;
                    vector<int> subpat;
                    for(int i = 0; i < 5; ++i) {
                        vector<int>::iterator it = find(v2.begin(), v2.end(), (~pat[i])&0x1f);
                        if(it == v2.end()) {
                            ok = false;
                            break;
                        }
                        else subpat.push_back(*it);
                    }
                    if(ok && !used.count(subpat)) ++ans;
                    for(int i = 0; i < 5; ++i) {
                        used.insert(pat);
                        used.insert(subpat);
                    }
                }
            } while(next_permutation(ord.begin(), ord.end()));
        } while(next_permutation(s.begin(), s.end()));

        cout << ans << endl;
    }

    return 0;
}
