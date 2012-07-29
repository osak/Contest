/*
 * Bの始点，終点それぞれの組み合わせについて，Aのsubsequenceになっているか確認する．
 * 確認は先頭からGreedyに合わせていけばよいので，O(B^2+A)で解ける．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int A, B;
    cin >> A >> B;

    vector<int> as(A), bs(B);
    for(int i = 0; i < A; ++i) {
        cin >> as[i];
    }
    for(int i = 0; i < B; ++i) {
        cin >> bs[i];
    }

    int ans = 0;
    for(int start = 0; start < B; ++start) {
        int aidx = 0;
        for(int end = start; end < B; ++end) {
            while(aidx < A && as[aidx] != bs[end]) ++aidx;
            if(aidx == A) break;
            ans = max(ans, end-start+1);
            ++aidx;
        }
    }

    cout << ans << endl;
    return 0;
}
