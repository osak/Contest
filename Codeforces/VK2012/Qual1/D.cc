#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_prime[20001];

void initprime() {
    fill(is_prime, is_prime+20001, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < 20001; ++i) {
        if(is_prime[i]) {
            for(int j = i*i; j < 20001; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int calc(const vector<int> &v, int start, int step) {
    int sum = 0;
    for(int i = start; i < v.size(); i += step) {
        sum += v[i];
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0);

    initprime();

    int N;
    cin >> N;
    vector<int> v(N);
    for(int i = 0; i < N; ++i) cin >> v[i];

    int ans = -1000*N;
    vector<vector<int> > cache(N+1);
    vector<bool> cached(N+1, false);
    for(int k = 3; k <= N; ++k) {
        if(N % k != 0) continue;
        
        int pat = N / k;
        if(is_prime[k]) {
            for(int start = 0; start < pat; ++start) {
                int sum = calc(v, start, N / k);
                ans = max(ans, sum);
                cache[k].push_back(sum);
            }
            cached[k] = true;
        }
        else {
            int divisor = 2;
            while(k % divisor != 0) ++divisor;
            if(!cached[divisor]) {
                for(int start = 0; start < N / divisor; ++start) {
                    int sum = calc(v, start, N / divisor);
                    cache[divisor].push_back(sum);
                }
                cached[divisor] = true;
            }
            for(int start = 0; start < pat; ++start) {
                int sum = calc(cache[divisor], start, N / k);
                ans = max(ans, sum);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
