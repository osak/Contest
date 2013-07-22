//Name: Signboard
//Level: 2
//Category: 文字列,全探索
//Note:

#include <iostream>
#include <string>

using namespace std;

bool check(const string &str, const string &target, int start) {
    const int SLEN = str.size();
    const int TLEN = target.size();
    for(int delta = 1; ; ++delta) {
        int pos = start;
        bool ok = true;
        for(int i = 0; i < TLEN; ++i) {
            if(pos >= SLEN) return false;
            if(str[pos] != target[i]) {
                ok = false;
                break;
            }
            pos += delta;
        }
        if(ok) return true;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    string target;
    cin >> N >> target;

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        const int L = str.size();
        for(int j = 0; j < L; ++j) {
            if(str[j] == target[0]) {
                if(check(str, target, j)) {
                    ++ans;
                    break;
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
