//Name: Stolen Jewel
//Level: 3
//Category: グラフ,Graph,Aho-Corasick
//Note: 

/**
 * Aho-Corasick法のオートマトンを作成し、(現在位置,Aho-Corasickのノード位置)で幅優先探索すればよい。
 *
 * オーダーはO(NMP|S|)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <tuple>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }

    operator T() {
        return valid ? val : T();
    }

    const T& fetch(const T &fallback) const {
        return valid ? val : fallback;
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

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};

bool solve(bool first) {
    int R, C;
    if(!(cin >> R >> C)) return false;
    if(!R && !C) return false;

    vector<string> field(R+2);
    pair<int,int> start, goal;
    field[0] = field[R+1] = string(C+2, '#');
    for(int r = 1; r < R+1; ++r) {
        cin >> field[r];
        field[r] = string("#") + field[r] + "#";
        for(int c = 1; c < C+2; ++c) {
            if(field[r][c] == 'S') {
                start = make_pair(r, c);
            } else if(field[r][c] == 'G') {
                goal = make_pair(r, c);
            }
        }
    }

    int P;
    cin >> P;
    vector<string> prohibited(P);
    for(int i = 0; i < P; ++i) {
        cin >> prohibited[i];
        for(char &c : prohibited[i]) {
            switch(c) {
            case 'R':
                c = 0;
                break;
            case 'U':
                c = 1;
                break;
            case 'L':
                c = 2;
                break;
            case 'D':
                c = 3;
                break;
            }
        }
    }
    AhoCorasick<4> am(prohibited); // Automaton
    vector<vector<vector<Maybe<int>>>> memo(R+2, vector<vector<Maybe<int>>>(C+2, vector<Maybe<int>>(am.size())));
    memo[start.first][start.second][0] = 0;
    queue<tuple<int,int,int>> q;
    q.push(make_tuple(start.first, start.second, 0));
    int ans = -1;
    while(!q.empty()) {
        int r, c, s;
        tie(r, c, s) = q.front();
        //cout << r << ' ' << c << ' ' << s << endl;
        q.pop();
        if(r == goal.first && c == goal.second) {
            ans = memo[r][c][s];
            break;
        }

        for(int i = 0; i < 4; ++i) {
            am.reset(s);
            const int nr = r + DR[i];
            const int nc = c + DC[i];
            const int ns = am.advance(i);
            if(field[nr][nc] == '#') continue;
            if(am.accepted()) continue;
            if(memo[nr][nc][ns].valid) continue;
            memo[nr][nc][ns] = memo[r][c][s] + 1;
            q.push(make_tuple(nr, nc, ns));
        }
    }
    cout << ans << endl;

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
