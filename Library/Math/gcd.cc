// Euclidean algorithm.
// Runs in O(log max(a, b))
template<typename T>
T gcd(T a, T b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        const T tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Used in:
// AOJ0115
