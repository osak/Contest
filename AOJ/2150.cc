//Name: Matsuzaki Number
//Level: 2
//Category: 素数
//Note:

/*
 * N以上の素数を50個くらい取ってきて組み合わせれば、100番目までの数は十分に列挙できる。
 *
 * オーダーは O(P log P)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_PRIME = 200000;
vector<int> primes;
bool is_prime[MAX_PRIME+1];

void init() {
    fill_n(is_prime, MAX_PRIME+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= MAX_PRIME; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(long long j = (long long)i*i; j <= MAX_PRIME; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

bool solve() {
    int N, P;
    cin >> N >> P;
    if(N == -1 && P == -1) return false;

    vector<int>::iterator first = upper_bound(primes.begin(), primes.end(), N);
    vector<int> nums;
    const int start = distance(primes.begin(), first);
    for(int i = start; i < start+100; ++i) {
        for(int j = i; j < start+100; ++j) {
            nums.push_back(primes[i]+primes[j]);
        }
    }
    sort(nums.begin(), nums.end());
    cout << nums[P-1] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    init();
    for(int case_num = 1; solve(); ++case_num) ;
    return 0;
}
