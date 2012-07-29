#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct Tag {
    int dir;
    int pos;

    Tag() {}
    Tag(int d, int p) : dir(d), pos(p) {}
};

typedef unsigned char byte;

int main() {
    int N, K;
    cin >> N >> K;

    vector<string> walls(2);
    cin >> walls[0];
    cin >> walls[1];

    vector<vector<byte> > memo(2, vector<byte>(N, 0));
    bool ans = false;
    queue<pair<int,Tag> > q;
    q.push(make_pair(0, Tag(0, 0)));
    while(!q.empty()) {
        int t = q.front().first;
        Tag tag = q.front().second;
        q.pop();

        // To goal
        if(tag.pos + K >= N) {
            ans = true;
            break;
        }

        // Up
        if(walls[tag.dir][tag.pos+1] == '-') {
            if(!memo[tag.dir][tag.pos+1]) {
                memo[tag.dir][tag.pos+1] = 1;
                q.push(make_pair(t+1, Tag(tag.dir, tag.pos+1)));
            }
        }

        // Down
        if(tag.pos-1 > t && walls[tag.dir][tag.pos-1] == '-') {
            if(!memo[tag.dir][tag.pos-1]) {
                memo[tag.dir][tag.pos-1] = 1;
                q.push(make_pair(t+1, Tag(tag.dir, tag.pos-1)));
            }
        }

        // Jump
        if(walls[1-tag.dir][tag.pos+K] == '-') {
            if(!memo[1-tag.dir][tag.pos+K]) {
                memo[1-tag.dir][tag.pos+K] = 1;
                q.push(make_pair(t+1, Tag(1-tag.dir, tag.pos+K)));
            }
        }
    }

    cout << (ans?"YES":"NO") << endl;

    return 0;
}
