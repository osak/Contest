#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool contains(const vector<int>& v, const vector<int>& k)
{
    const int M = v.size(), K = k.size();
    if (M == 0) {
        return false;
    }
    int i = 0, j = 0;
    for (; i < M && j < K; i++) {
        if (v[i] == k[j]) {
            j++;
        }
    }
    return j == K;
}

int solve(const vector<vector<int> >& v, const vector<int>& k)
{
    const int N = v.size();
    int idx = -1;
    for (int i = 0; i < N; i++) {
        if (contains(v[i], k)) {
            if (idx != -1) {
                return -1;
            }
            idx = i+1;
        }
    }
    return idx;
}

int main()
{
    int N;
    while (cin >> N && N != 0) {
        vector<vector<int> > v(N);
        for (int i = 0; i < N; i++) {
            int M;
            cin >> M;
            v[i].resize(M);
            for (int j = 0; j < M; j++) {
                cin >> v[i][j];
            }
            sort(v[i].begin(), v[i].end());
        }
        int K;
        cin >> K;
        vector<int> k(K);
        for (int i = 0; i < K; i++) {
            cin >> k[i];
        }
        sort(k.begin(), k.end());

        cout << solve(v, k) << endl;
    }
    return 0;
}
