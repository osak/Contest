#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<bool> isprime(10001, true);
    isprime[0] = isprime[1] = false;
    for(int i = 2; i <= 100; ++i) {
        if(!isprime[i]) continue;
        for(int j = i*i; j < isprime.size(); j += i) isprime[j] = false;
    }

    while(true) {
        int N;
        cin >> N;
        if(cin.eof()) break;

        int cnt = 0;
        for(int i = 1; i <= N; ++i) {
            if(isprime[i] && isprime[N+1-i]) ++cnt;
        }
        cout << cnt << endl;
    }
    return 0;
}
