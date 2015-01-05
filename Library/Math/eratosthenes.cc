// Sieve of eratosthenes.
// Runs in O(N log log N).
vector<bool> eratosthenes(int N) {
    vector<bool> is_prime(N+1, true);
    is_prime[0] = is_prime[1] = false;

    const int LIM = static_cast<int>(sqrt(N));
    for(long long i = 2; i <= LIM; ++i) {
        if(is_prime[i]) {
            for(long long j = i*i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Used in:
// AOJ0150
