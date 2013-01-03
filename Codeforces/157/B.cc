#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
int numbers[11][11];
long long pat[100];

void calcpat(int L) {
    int pats = 1;
    for(int i = 0; i < 6; ++i) {
        pats *= L+1;
    }
    vector<int> cnt(11, 0);
    for(int p = 0; p < pats; ++p) {
        fill(cnt.begin(), cnt.end(), 0);
        int sum = 0;
        long long acc = 0;
        int tmp = p;
        bool valid = true;
        for(int i = 0; i < 6; ++i) {
            const int s = tmp % (L+1);
            sum += s;
            acc += numbers[L][s];
            acc %= MOD;
            tmp /= L+1;
            if(++cnt[s] > numbers[L][s]) {
                valid = false;
                break;
            }
        }
        if(valid) {
            pat[sum] += acc;
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    ++N;
    int L = 0;
    {
        int tmp = N;
        while(tmp > 0) {
            L++;
            tmp /= 10;
        }
    }

    vector<int> nd(L);
    {
        int tmp = N;
        for(int i = 0; i < L; ++i) {
            nd[i] = tmp % 10;
            tmp /= 10;
        }
        reverse(nd.begin(), nd.end());
    }

    numbers[0][0] = 1;

    // 1 digits to L-1 digits
    // Allowing leading zero
    for(int digits = 1; digits <= L-1; ++digits) {
        for(int cnt = 0; cnt <= digits; ++cnt) {
            numbers[digits][cnt] = numbers[digits-1][cnt]*8 + numbers[digits-1][cnt-1]*2;
        }
    }

    // L digits
    // Not allowing leading zero
    int acc = 0;
    for(int pos = 0; pos < L; ++pos) {
        const int inf = (pos == 0) ? 1 : 0;
        const int sup = nd[pos];
        for(int digit = inf; digit < sup; ++digit) {
            for(int cnt = 0; cnt <= L; ++cnt) {
                const int prevcnt = cnt - acc - (digit == 4 || digit == 7) ? 1 : 0;
                if(prevcnt >= 0) numbers[L][cnt] += numbers[L-1][prevcnt];
            }
        }
        if(sup == 4 || sup == 7) ++acc;
    }
    //cout << numbers[L][0] << endl;

    calcpat(L);
    long long ans = 0;
    for(int mycnt = 0; mycnt <= L; ++mycnt) {
        for(int sum = 0; sum < mycnt; ++sum) {
            ans += pat[sum];
            ans %= MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
