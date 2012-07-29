#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Tag {
    int to;
    string str;

    Tag() {}
    Tag(int to, const string &str) : to(to), str(str) {}
};

int main() {
    while(true) {
        int N, A, S, G;
        cin >> N >> A >> S >> G;
        if(!N && !A && !S && !G) break;

        vector<vector<Tag> > v(N);
        for(int i = 0; i < A; ++i) {
            Tag t;
            int x;
            cin >> x >> t.to >> t.str;
            v[x].push_back(t);
        }

        vector<string> best(N, "\xFF");
        vector<int> goalable(N, 0);
        bool noans = false;
        best[G] = "";
        goalable[G] = 1;
        for(int TURN = 0; TURN < N; ++TURN) {
            vector<string> next = best;
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < v[i].size(); ++j) {
                    const Tag &tag = v[i][j];
                    const string str = tag.str + best[tag.to];
                    if(goalable[tag.to] && str < next[i]) {
                        next[i] = str;
                        goalable[i] = 1;
                    }
                }
            }
            best = next;
        }

        bool hasloop = false;
        for(int TURN = 0; TURN < 6*N; ++TURN) {
            vector<string> next = best;
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < v[i].size(); ++j) {
                    const Tag &tag = v[i][j];
                    const string str = tag.str + best[tag.to];
                    if(goalable[tag.to] && str < next[i]) {
                        next[i] = str;
                        goalable[i] = 1;
                        if(i == S) hasloop = true;
                    }
                }
            }
            best = next;
        }       

        if(hasloop || best[S] == "\xFF") cout << "NO" << endl;
        else cout << best[S] << endl;
    }
    return 0;
}
