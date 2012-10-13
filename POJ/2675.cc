//Name: Songs
//Level: 3
//Category: 数論
//Note: サンプルは1ケースだが複数ケース来る

/*
 * length / freq でソートして，その順で使えばよい．
 *
 * ある並べ方があって，仮に l_i / f_i ≧ l_(i+1) / f_(i+1) だったとすると，これを入れ換えることで
 * -f_(i+1)*l_i + f_(i)*l_(i+1) だけ目的関数が変化することになる．
 * ここで上の式より，この差分は負であるから入れ換えたほうが目的関数の最小化に貢献する．
 * これを更新できなくなるまで続けていくと，どんな状態からでも最終的には length / freq でソートされた順番になるので，これが最小である．
 *
 * オーダーは O(N log N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Tag {
    unsigned id;
    int length;
    double freq;

    bool operator < (const Tag &other) const {
        return length*other.freq < other.length*freq;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    while(cin >> N) {
        vector<Tag> songs(N);
        for(int i = 0; i < N; ++i) {
            Tag &t = songs[i];
            cin >> t.id >> t.length >> t.freq;
        }
        sort(songs.begin(), songs.end());
        int S;
        cin >> S;
        cout << songs[S-1].id << endl;
    }

    return 0;
}
