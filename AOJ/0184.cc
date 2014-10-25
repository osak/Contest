//Name: Tsuruga Castle
//Level: 1
//Category: 実装
//Note:

/**
 * 年齢 / 10 でビンに分ける。
 * 60歳以上を特別扱いすることに注意。
 */
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    array<int,7> bins;
    fill(begin(bins), end(bins), 0);

    for(int i = 0; i < N; ++i) {
        int age;
        cin >> age;
        age /= 10;
        if(age > 6) age = 6;
        bins[age]++;
    }
    for(int i = 0; i < 7; ++i) {
        cout << bins[i] << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
