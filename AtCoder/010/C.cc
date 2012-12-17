#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <tr1/unordered_map>
#include <string>

using namespace std;
using namespace tr1;

struct Tag {
    int used, color;
    Tag(int u, int col) : used(u), color(col) {}

    bool operator ==(const Tag &other) const {
        return  used == other.used && 
                color == other.color;
    }
};

struct Hasher {
    size_t operator ()(const Tag &tag) const {
        return tag.used*10 + tag.color;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, M, Y, Z;
    cin >> N >> M >> Y >> Z;
    vector<int> colortbl(26, 0), scoretbl(10, 0);
    for(int i = 0; i < M; ++i) {
        char color;
        int score;
        cin >> color >> score;
        colortbl[color-'A'] = i;
        scoretbl[i] = score;
    }
    const int FULLCOLOR = (1<<M)-1;
    string blocks;
    cin >> blocks;

    typedef unordered_map<Tag,int,Hasher> MemoType;
    MemoType memo[2];
    memo[0][Tag(0, -1)] = 0;
    for(string::const_iterator it = blocks.begin(); it != blocks.end(); ++it) {
        const int color = colortbl[*it-'A'];
        const int mask = (1<<color);
        memo[1] = memo[0];
        for(MemoType::iterator it = memo[0].begin(); it != memo[0].end(); ++it) {
            const Tag &t = it->first;
            int score = it->second;
            {
                // Put
                Tag nt = t;
                int ns = score + scoretbl[color];
                nt.used |= mask;
                if(t.used != FULLCOLOR && nt.used == FULLCOLOR) {
                    ns += Z;
                }
                if(nt.color == color) {
                    ns += Y;
                } else {
                    nt.color = color;
                }
                if(memo[1].count(nt)) {
                    memo[1][nt] = max(memo[1][nt], ns);
                } else {
                    memo[1][nt] = ns;
                }
            }
        }
        memo[0].swap(memo[1]);
    }
    int ans = 0;
    for(MemoType::iterator it = memo[0].begin(); it != memo[0].end(); ++it) {
        ans = max(ans, it->second);
    }
    cout << ans << endl;
    return 0;
}
