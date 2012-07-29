#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

using namespace std;

string fmt(int t) {
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", t/3600, t/60%60, t%60);
    return string(buf);
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<pair<int, int> > candidates;
        for(int i = 0; i < N; ++i) {
            int hands[3];
            int pat[] = {1, 60, 3600};
            cin >> hands[0] >> hands[1] >> hands[2];

            for(int r = 0; r < 60; ++r) {
                do {
                    int sec = 0;
                    int midx, hidx;

                    for(int j = 0; j < 3; ++j) {
                        if(pat[j] == 3600) hidx = j;
                        else if(pat[j] == 60) midx = j;

                        if(pat[j] == 3600) sec += hands[j] / 5 * pat[j];
                        else sec += hands[j] * pat[j];
                    }
                    if(hands[hidx] % 5 != hands[midx] / 12) continue;

                    candidates.push_back(make_pair(sec, i));
                } while(next_permutation(pat, pat+3));
                for(int k = 0; k < 3; ++k) {
                    hands[k] = (hands[k]+1) % 60;
                }
            }
        }

        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        vector<int> avail(N, 0);
        int availcnt = 0;
        int start = 0, end = candidates.size()-1;
        int cur_start = 0, cur_end = 0;
        for(int i = 0; i < candidates.size(); ++i) {
            int t = candidates[i].first;
            int watch = candidates[i].second;

            if(!avail[watch]++) availcnt++;

            while(avail[candidates[cur_start].second] > 1) {
                avail[candidates[cur_start].second]--;
                cur_start++;
            }

            cur_end = i;
            if(availcnt == N) {
                int d1 = candidates[cur_end].first - candidates[cur_start].first;
                int d2 = candidates[end].first - candidates[start].first;
                if(d1 >= 0 && d1 < d2) {
                    start = cur_start;
                    end = cur_end;
                    /*
                    cout << start << ' ' << end << endl;
                    for(int j = start; j <= end; ++j) {
                        cout << candidates[j].second << '(' << avail[candidates[j].second] << ')' << ' ';
                    }
                    cout << endl;
                    */
                }
            }
        }

        cout << fmt(candidates[start].first) << ' ' << fmt(candidates[end].first) << endl;
    }
    return 0;
}
