#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

inline int c2i(char c) {
    if(islower(c)) return c-'a';
    return 26+c-'A';
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        string B, S;
        cin >> B >> S;

        vector<int> needed(52, 0);
        vector<int> cnt(52, 0);
        for(int i = 0; i < B.size(); ++i) needed[c2i(B[i])] = true;

        int ans = M;
        int inc = 0;
        int left = 0;
        for(int i = 0; i < S.size(); ++i) {
            int cc = c2i(S[i]);
            if(!needed[cc]) continue;

            if(cnt[cc] == 0) inc++;
            cnt[cc]++;
            if(inc == B.size()) {
                while(left < i) {
                    int dc = c2i(S[left]);
                    if(!needed[dc] || cnt[dc] > 1) {
                        left++;
                        cnt[dc]--;
                    }
                    else break;
                }
                ans = min(ans, i-left+1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
