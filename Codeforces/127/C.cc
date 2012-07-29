#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

int a[100000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    for(int i = 0; i < N-1; ++i) {
        cin >> a[i];
    }

    ULL best_score = 0;
    {
        ULL score = 0;
        for(int i = 0; i < N-1; ++i) {
            if(a[i] % 2 == 1) {
                score += a[i];
            }
            else {
                ULL tmp = score + a[i];
                if(tmp > best_score) best_score = tmp;
                score += a[i]-1;
            }
            best_score = max(best_score, score);
        }
    }

    {
        ULL score = 0;
        for(int i = N-2; i >= 0; --i) {
            if(a[i] % 2 == 1) {
                score += a[i];
            }
            else {
                ULL tmp = score + a[i];
                if(tmp > best_score) best_score = tmp;
                score += a[i]-1;
            }
            best_score = max(best_score, score);
        }
    }

    cout << best_score << endl;
    return 0;
}

