#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;

const string note[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

int main() {
    int N;
    cin >> N;

    while(N--) {
        int n, m;
        cin >> n >> m;

        vector<int> stairs;
        vector<int> music;
        for(int i = 0; i < n; ++i) {
            char buf[256];
            scanf(" %s", buf);
            for(int j = 0; j < 12; ++j) {
                if(note[j] == buf) {
                    stairs.push_back(j);
                    break;
                }
            }
        }
        for(int i = 0; i < m; ++i) {
            char buf[256];
            scanf(" %s", buf);
            for(int j = 0; j < 12; ++j) {
                if(note[j] == buf) {
                    music.push_back(j);
                    break;
                }
            }
        }

        vector<int> cache(n, 0);
        priority_queue<pair<int, int> > q;
        q.push(make_pair(1, -1));

        bool ok = false;
        while(!q.empty()) {
            int to_play = -q.top().first+1;
            int pos = q.top().second;
            q.pop();

            if(to_play == m) {
                if(pos >= n-2) {
                    ok = true;
                    break;
                }
                else continue;
            }
            if(cache[pos] >= to_play) continue;

            if(pos-1 >= 0) {
                if((stairs[pos-1]+11)%12 == music[to_play]) {
                    if(to_play+1 > cache[pos-1]) {
                        cache[pos-1] = to_play+1;
                        q.push(make_pair(-to_play, pos-1));
                    }
                }
            }
            if(pos+2 < n) {
                if((stairs[pos+2]+1)%12 == music[to_play]) {
                    if(to_play+1 > cache[pos+2]) {
                        cache[pos+2] = to_play+1;
                        q.push(make_pair(-to_play, pos+2));
                    }
                }
            }
            if(pos+1 < n) {
                if(stairs[pos+1] == music[to_play]) {
                    if(to_play+1 > cache[pos+1]) {
                        cache[pos+1] = to_play+1;
                        q.push(make_pair(-to_play, pos+1));
                    }
                }
            }
        }
        cout << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}
