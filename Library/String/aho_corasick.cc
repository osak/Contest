// Aho-Corasick algorithm.
// Characters must be in range [0, CharNum)
//
// O(Σ|S||C|) for build.
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

// Used in:
// AOJ2212
