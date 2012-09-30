//Name: Flying Jenny
//Level: 1
//Category: やるだけ
//Note:

/*
 * メリーゴーランドを実際に回しながら余る人数を調べる．
 */
#include <iostream>
#include <deque>
#include <climits>

using namespace std;

const int _MERRY[] = {4, 1, 4, 1, 2, 1, 2, 1};
int arr[8];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        for(int i = 0; i < 8; ++i) {
            cin >> arr[i];
        }
        if(cin.eof()) break;

        deque<int> MERRY(_MERRY, _MERRY+8), ans(8, 9);
        int best = INT_MAX;
        for(int start = 0; start < 8; ++start) {
            int rem = 0;
            for(int i = 0; i < 8; ++i) {
                rem += max(0, arr[i] - MERRY[i]);
            }
            if(rem < best || (rem == best && MERRY < ans)) {
                ans = MERRY;
                best = rem;
            }
            MERRY.push_back(MERRY[0]);
            MERRY.pop_front();
        }
        for(int i = 0; i < 8; ++i) {
            if(i > 0) cout << ' ';
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
