//Name: Unique number
//Level: 1
//Category: やるだけ
//Note:
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int> > v(3, vector<int>(N));
    vector<int> score(N, 0);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 3; ++j) {
            cin >> v[j][i];
        }
    }

    for(int j = 0; j < 3; ++j) {
        map<int,int> cnt;
        for(int i = 0; i < N; ++i) {
            cnt[v[j][i]]++;
        }
        for(int i = 0; i < N; ++i) {
            if(cnt[v[j][i]] == 1) {
                score[i] += v[j][i];
            }
        }
    }

    for(int i = 0; i < N; ++i) {
        cout << score[i] << endl;
    }
    return 0;
}
