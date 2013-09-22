//Name: Almost Same String
//Level: 4
//Category: 文字列,ハッシュ
//Note:

/*
 * ローリングハッシュを使ってSの内容をすべてキャッシュしておく。
 * 次に、Tに対して考えられる異なりをすべて列挙しながら上のハッシュを検索する。
 * オーダーはO(|T| log |S|)。
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;
const ULL PRIME = 1019;

ULL fastpow(ULL a, int x) {
    ULL res = 1;
    ULL ord = a;
    while(x) {
        if(x & 1) {
            res *= ord;
        }
        ord *= ord;
        x >>= 1;
    }
    return res;
}

int c2i(char c) {
    if(isupper(c)) return c - 'A';
    else return 26+c-'a';
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string S, T;
    getline(cin, S);
    getline(cin, T);
    const int M = S.size();
    const int N = T.size();
    vector<int> s(M), t(N);
    for(int i = 0; i < M; ++i) {
        s[i] = c2i(S[i]);
    }
    for(int i = 0; i < N; ++i) {
        t[i] = c2i(T[i]);
    }

    unordered_map<ULL,int> cnt;
    ULL hash = 0;
    const ULL top = fastpow(PRIME, N-1);
    for(int i = 0; i < M; ++i) {
        hash *= PRIME;
        hash += s[i];
        if(i+1 >= N) {
            cnt[hash]++;
            hash -= top * s[i+1-N];
        }
    }

    ULL t_hash = 0;
    for(int i = 0; i < N; ++i) {
        t_hash *= PRIME;
        t_hash += t[i];
    }
    ULL ord = 1;
    int ans = 0;
    for(int i = N-1; i >= 0; --i) {
        ULL tmp = t_hash - ord*t[i];
        for(int c = 0; c < 52; ++c) {
            if(t[i] == c) continue;
            ULL h = tmp + ord*c;
            //cout << h << endl;
            if(cnt.count(h)) ans += cnt[h];
        }
        ord *= PRIME;
    }
    cout << ans << endl;
    return 0;
}
