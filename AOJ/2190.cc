#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <cstdio>
#include <set>

using namespace std;

const string note[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

int main() {
    int N;
    cin >> N;
    //N = 1;

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

        bool ok = false;
        for(int start = n-2; start <= n-1; ++start) {
            if(start < 0) continue;
            int mpos = m-1;
            int pos = start;
            for(; mpos >= 0; --mpos) {
                if(stairs[pos] == music[mpos]) {
                    if(--pos < 0) goto next;
                }
                else if((stairs[pos]+1)%12 == music[mpos]) {
                    pos -= 2;
                    if(pos < 0) goto next;
                }
                else if((stairs[pos]+11)%12 == music[mpos]) {
                    pos += 1;
                    if(pos >= n) goto next;
                }
                else break;
            }
next:
            if(mpos <= 0 && pos == -1) {
                ok = true;
                break;
            }
        }
        cout << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}
