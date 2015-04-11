#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

enum UNIT {
    ONE,
    I,
    J,
    K
};

struct Quaternion {
    UNIT unit;
    bool negative;

    Quaternion() : unit(ONE), negative(false) {}
    Quaternion(UNIT unit) : unit(unit), negative(false) {}
    Quaternion(UNIT unit, bool negative) : unit(unit), negative(negative) {}
};

Quaternion mul_table[4][4] = {
    {Quaternion(ONE), Quaternion(I), Quaternion(J), Quaternion(K)},
    {Quaternion(I), Quaternion(ONE, true), Quaternion(K), Quaternion(J, true)},
    {Quaternion(J), Quaternion(K, true), Quaternion(ONE, true), Quaternion(I)},
    {Quaternion(K), Quaternion(J), Quaternion(I, true), Quaternion(ONE, true)}
};

Quaternion operator -(const Quaternion &q) {
    return Quaternion(q.unit, !q.negative);
}

Quaternion operator *(const Quaternion &q1, const Quaternion &q2) {
    Quaternion u = mul_table[q1.unit][q2.unit];
    if(q1.negative ^ q2.negative) return -u;
    return u;
}

Quaternion operator /(const Quaternion &q1, const Quaternion &q2) {
    if(q2.unit == ONE && !q2.negative) return q1;
    if(q2.unit == ONE && q2.negative) return -q1;
    return q1 * Quaternion(q2.unit, q2.negative ^ true);
}

Quaternion inv(const Quaternion &q) {
    return Quaternion(ONE) / q;
}

string solve(int CASE) {
    long long L, X;
    cin >> L >> X;
    string str;
    cin >> str;

    const long long len = min(L*X, L*(12 + X%4));
    vector<Quaternion> acc(len);
    for(int i = 0; i < L; ++i) {
        Quaternion q;
        switch(str[i]) {
        case 'i':
            q = Quaternion(I);
            break;
        case 'j':
            q = Quaternion(J);
            break;
        case 'k':
            q = Quaternion(K);
            break;
        default:
            assert(false);
        }
        for(int j = i; j < len; j += L) {
            acc[j] = q;
        }
    }
    for(int i = 1; i < len; ++i) {
        acc[i] = acc[i-1] * acc[i];
    }
    for(int i = 0; i < min(len, L*4); ++i) {
        if(acc[i].unit != I || acc[i].negative) continue;
        for(int k = max((long long)i, len-L*4); k < len-1; ++k) {
            Quaternion q = inv(acc[k]) * acc[len-1];
            if(q.unit != K || q.negative) continue;
            //cout << i << ' ' << k << endl;
            Quaternion j = inv(acc[i]) * acc[k];
            if(j.unit == J && !j.negative) {
                return "YES";
            }
        }
    }
    return "NO";
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        cout << "Case #" << CASE << ": " << solve(CASE) << endl;
    }
    return 0;
}
