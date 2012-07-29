#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstring>
#include <cassert>

using namespace std;

const int MOD = 1000000007;

struct Node {
    int id;
    bool terminal;
    int next[26];
    int failure;

    Node(int id, bool term) : id(id), terminal(term), failure(0) {
        fill(next, next+26, 0);
    }

    int getnext(char c) const {
        int n = next[c-'a'];
        if(n == 0) return failure;
        return n;
    }

    bool hasnext(char c) const {
        return next[c-'a'] != 0;
    }

    int set(char c, int n) {
        next[c-'a'] = n;
    }
};

int& add(int &lhs, const int &rhs) {
    lhs += rhs;
    lhs %= MOD;
    return lhs;
}

int main() {
    while(true) {
        int N, M, K;
        cin >> N >> M >> K;
        if(!N && !M && !K) break;

        int seq = 0;
        map<string,int> s2i;
        vector<vector<int> > v(N+3, vector<int>(N+3, 0));
        vector<string> words;
        words.push_back("");
        for(int i = 0; i < N; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            int i1, i2;
            if(s2i.count(s1) == 0) {
                s2i[s1] = words.size();
                words.push_back(s1);
            }
            if(s2i.count(s2) == 0) {
                s2i[s2] = words.size();
                words.push_back(s2);
            }
            i1 = s2i[s1]; i2 = s2i[s2];
            v[i1][i2] = 1;
            assert(i1 < N+3);
            assert(i2 < N+3);
        }
        const int L = words.size();
        for(int i = 1; i < L; ++i) {
            v[0][i] = 1;
        }

        vector<string> kigo(K);
        vector<Node> trie;
        trie.push_back(Node(0, false));
        for(int i = 0; i < K; ++i) {
            int pos = 0;
            cin >> kigo[i];
            for(int j = 0; j < kigo[i].size(); ++j) {
                if(j+1 < kigo[i].size() && !trie[pos].hasnext(kigo[i][j])) {
                    Node n(trie.size(), false);
                    int next = n.id;
                    trie.push_back(n);
                    trie[pos].set(kigo[i][j], next);
                }
                else if(j+1 == kigo[i].size()) {
                    trie[pos].terminal = true;
                }
                 pos = trie[pos].getnext(kigo[i][j]);
            }
        }

        queue<pair<int, string> > q;
        q.push(make_pair(0, ""));
        while(!q.empty()) {
            int node = q.front().first;
            string str = q.front().second;
            q.pop();

            Node &n = trie[node];
            for(char c = 'a'; c <= 'z'; ++c) {
                if(n.hasnext(c)) {
                    int next = n.getnext(c);
                    for(char d = 'a'; d <= 'z'; ++d) {
                        trie[next].failure = trie[n.failure].getnext(c);
                    q.push(make_pair(next, str+c));
                    cerr << next << " failure sets to " << trie[n.failure].getnext(c) << endl;
                }
            }
        }

        int dp[M+1][trie.size()][L][2];
        memset(dp, 0, sizeof(dp));

        dp[0][0][0][0] = 1;
        for(int m = 0; m <= M; ++m) {
            for(int p = 0; p < trie.size(); ++p) {
                for(int n = 0; n < L; ++n) {
                    if(dp[m][p][n][0] == 0 && dp[m][p][n][1] == 0) continue;
                    for(int i = 0; i < L; ++i) {
                        const string &str = words[i];
                        if(!v[n][i]) continue;
                        if(m + str.size() > M) continue;

                        cerr << m << ' ' << p << ' ' << n << ' ' << i << endl;
                        int kigo_cnt = 0;
                        int pos = p;
                        for(int j = 0; j < str.size(); ++j) {
                            int next = trie[pos].getnext(str[j]);
                            if(trie[next].terminal) ++kigo_cnt;
                            pos = next;
                        }
                        assert(pos < trie.size());
                        if(kigo_cnt == 0) {
                            add(dp[m+str.size()][pos][i][0], dp[m][p][n][0]);
                            add(dp[m+str.size()][pos][i][1], dp[m][p][n][1]);
                        }
                        else if(kigo_cnt == 1) {
                            add(dp[m+str.size()][pos][i][1], dp[m][p][n][0]);
                        }
                    }
                }
            }
        }
        int sum = 0;
        for(int p = 0; p < trie.size(); ++p) {
            for(int n = 0; n < L; ++n) {
                add(sum, dp[M][p][n][1]);
            }
        }
        cout << sum << endl;
    }
    return 0;
}
