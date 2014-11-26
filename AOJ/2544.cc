//Name: Older Research Bldg. No.7
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

/**
 * 入力がソートされているため、目的の年を超える入力が来た時点で、その直前の名称を出せばよい。
 * オーダーは O(N)。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve() {
    int N, Q;
    if(!(cin >> N >> Q)) return false;

    string name = "kogakubu10gokan";
    for(int i = 0; i < N; ++i) {
        int y;
        string n;
        cin >> y >> n;
        if(y > Q) break;
        name = n;
    }
    cout << name << endl;
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
