//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(const T &t) : val(t), valid(true) {}
    Maybe(const Maybe<T> &m) : valid(m.valid) {
        if(valid) val = m.val;
    }

    const T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return rv;
    }

    const Maybe<T>& operator =(const Maybe<T> &rv) {
        if(rv.valid) val = rv.val;
        valid = rv.valid;
        return rv;
    }

    const Maybe<T>& operator +=(const Maybe<T> &rv) {
        if(!valid && !rv.valid) return *this;
        if(!valid) *this = T();
        if(rv.valid) val += rv.val;
        return *this;
    }

    const T& fetch(const T &fallback) const {
        return valid ? val : fallback;
    }

    operator T() const {
        return valid ? val : T();
    }

    template<typename Cond>
    bool update(const T &v, Cond cond) {
        if(!valid || cond(v, val)) {
            val = v;
            valid = true;
            return true;
        }
        return false;
    }

    bool update(const T &v) {
        return update(v, less<T>());
    }
};/*}}}*/

// Aho-Corasick algorithm.
// Characters must be in range [0, CharNum)
//
// O(裡|S||C|) for build.
template<int CharNum>
struct AhoCorasick {
    struct Node {
        bool terminal;
        int failure;
        array<Maybe<int>,CharNum> edge;
        Node() : terminal(false), failure(0) {
            fill(begin(edge), end(edge), Maybe<int>());
        }
    };

    vector<Node> g_;
    int pos_;

    AhoCorasick(const vector<string> &dict) {
        g_.resize(1);

        // Build trie
        for(const auto &s : dict) {
            int cur = 0;
            for(const int c : s) {
                if(!g_[cur].edge[c].valid) {
                    g_.push_back(Node());
                    g_[cur].edge[c] = (int)g_.size() - 1;
                }
                cur = g_[cur].edge[c];
            }
            g_[cur].terminal = true;
        }

        // Build failure link
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            const int cur = q.front();
            q.pop();
            for(int ch = 0; ch < CharNum; ++ch) {
                if(g_[cur].edge[ch].valid) {
                    const int n = g_[cur].edge[ch].val;
                    q.push(n);
                    int f = g_[cur].failure;
                    while(f != 0 && !g_[f].edge[ch].valid) {
                        f = g_[f].failure;
                    }
                    g_[n].failure = g_[f].edge[ch].fetch(0);
                    if(g_[n].failure == n) g_[n].failure = 0;
                }
            }
        }

        // Update terminal state
        for(auto &n : g_) {
            int f = n.failure;
            while(f != 0) {
                if(g_[f].terminal) {
                    n.terminal = true;
                    break;
                }
                f = g_[f].failure;
            }
        }
    }

    void reset(int pos = 0) {
        pos_ = pos;
    }

    int advance(int ch) {
        while(pos_ != 0 && !g_[pos_].edge[ch].valid) {
            pos_ = g_[pos_].failure;
        }
        pos_ = g_[pos_].edge[ch].fetch(0);
        return pos_;
    }

    int size() const {
        return g_.size();
    }

    bool accepted() const {
        return g_[pos_].terminal;
    }
};

array<array<array<Maybe<double>,110>,110>,110> dp;
double solve() {
    int K, L, S;
    string KEYS, TARGET;
    cin >> K >> L >> S;
    cin >> KEYS >> TARGET;

    for(int i = 0; i < 110; ++i) {
        for(int j = 0; j < 110; ++j) {
            for(int k = 0; k < 110; ++k) {
                dp[i][j][k] = Maybe<double>();
            }
        }
    }
    vector<double> prob(26, 0);
    for(char c : KEYS) {
        prob[c-'A'] += 1.0 / KEYS.size();
    }
    for(char &c : TARGET) {
        c -= 'A';
    }
    vector<string> V = {TARGET};
    AhoCorasick<26> ac(V);

    dp[0][0][0] = 1.0;
    for(int turn = 0; turn < S; ++turn) {
        for(int node = 0; node < ac.size(); ++node) {
            for(int cnt = 0; cnt <= S; ++cnt) {
                if(!dp[turn][node][cnt].valid) continue;
                for(int i = 0; i < 26; ++i) {
                    if(prob[i] == 0) continue;
                    ac.reset(node);
                    const int np = ac.advance(i);
                    if(ac.accepted()) dp[turn+1][np][cnt+1] += dp[turn][node][cnt] * prob[i];
                    else dp[turn+1][np][cnt] += dp[turn][node][cnt] * prob[i];
                }
            }
        }
    }

    int maxv = 0;
    double expect = 0;
    for(int node = 0; node < ac.size(); ++node) {
        for(int cnt = 0; cnt <= S; ++cnt) {
            if(dp[S][node][cnt].valid) {
                maxv = max(maxv, cnt);
                expect += cnt * dp[S][node][cnt];
            }
        }
    }
    //cout << maxv << ' ' << expect << endl;
    return maxv - expect;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": " << solve() << endl;
    }
    return 0;
}
