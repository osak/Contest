//Name: Encryption System
//Level: 3
//Category: 全探索
//Note:

/**
 * アルファベット順で1つ前の文字にずらされるため、1つの文字は高々1回しか置換されない。
 * 文字列長が最大20文字と短いため、どの文字が置換されたかの候補をすべて試し、実際に変換してみて元に戻るかを確かめればよい。
 *
 * オーダーは O(2^|S| × |S|)。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <array>

using namespace std;

bool solve() {
    string str;
    if(!(cin >> str)) return false;
    if(str == "#") return false;

    const int N = str.size();
    vector<string> ans;
    array<int,26> first_pos;
    for(int i = 0; i < (1<<N); ++i) {
        string cand = str;
        bool ok = true;
        int popcnt = 0;
        for(int j = 0; j < N; ++j) {
            if(i & (1<<j)) {
                ++popcnt;
                if(cand[j] == 'z') {
                    ok = false;
                    break;
                }
                cand[j] = cand[j]+1;
            }
        }
        if(ok) {
            fill(begin(first_pos), end(first_pos), -1);
            for(int j = 0; j < N; ++j) {
                const char ch = cand[j] - 'a';
                if(first_pos[ch] != -1 && (i & (1<<j))) {
                    ok = false;
                    break;
                }
                if(first_pos[ch] == -1 && ch != 0) {
                    if(i & (1<<j)) {
                        --popcnt;
                    } else {
                        ok = false;
                        break;
                    }
                    first_pos[ch] = j;
                }
            }
            if(ok && popcnt == 0) {
                ans.push_back(cand);
            }
        }
    }

    sort(begin(ans), end(ans));
    ans.erase(unique(begin(ans), end(ans)), end(ans));
    cout << ans.size() << endl;
    if(ans.size() <= 10) {
        for(const string &s : ans) {
            cout << s << endl;
        }
    } else {
        for(int i = 0; i < 5; ++i) {
            cout << ans[i] << endl;
        }
        for(int i = 0; i < 5; ++i) {
            cout << *(ans.rbegin()+4-i) << endl;
        }
    }

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
