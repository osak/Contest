#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) {
        unsigned nums[8];
        unsigned sum = 0;
        cin >> std::hex;
        for(int i = 0; i < 8; ++i) cin >> nums[i];
        cin >> sum;

        unsigned K = 0;
        for(int i = 0; i < 32; ++i) {
            unsigned carry = 0;
            for(int j = 0; j < 8; ++j) carry += (nums[j]^K)&((1<<i)-1);
            unsigned subsum = 0;
            for(int j = 0; j < 8; ++j) subsum += (nums[j]>>i)&1;
            unsigned sumbit = (sum>>i)&1;
            sumbit ^= (carry>>i)&1;

            if((subsum&1) != sumbit) K |= (1<<i);
        }

        cout << std::hex << K << endl;
    }

    return 0;
}
