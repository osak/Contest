//Name: Questionnaire
//Level: 2
//Category: ソート,やるだけ
//Note:

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int,int> Entry;

bool cmp(const Entry &e1, const Entry &e2) {
    if(e1.first != e2.first) return e1.first > e2.first;
    return e1.second < e2.second;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Entry> cnt(M);
        for(int i = 0; i < M; ++i) {
            cnt[i].first = 0;
            cnt[i].second = i+1;
        }
        while(N--) {
            for(int i = 0; i < M; ++i) {
                int f;
                cin >> f;
                if(f == 1) cnt[i].first++;
            }
        }
        sort(cnt.begin(), cnt.end(), cmp);
        for(int i = 0; i < M-1; ++i) {
            cout << cnt[i].second << ' ';
        }
        cout << cnt[M-1].second << endl;
    }
    return 0;
}
