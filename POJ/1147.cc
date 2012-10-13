//Name: Binary codes
//Level: 3
//Category: 数論,置換
//Note:

/*
 * ブロックソートとして知られているアルゴリズム(bzip2に使われている)．
 * http://ja.wikipedia.org/wiki/ブロックソート
 *
 * 最後のカラムだけ与えられたとき，これを右に1回巡回シフトすると先頭カラムの列が得られる．
 * このとき，元の列は全て異なるシフト回数の数列であるから，ここで得られた先頭カラム列もすべて異なる
 * シフト回数の数列である．
 * また，条件よりこの表はソート済みなので，先頭カラムはソートされている．
 * したがって，巡回シフトで得られたカラム列をソートすることで，表の先頭カラムがどうなっているかが全て分かる．
 *
 * 同様にして先頭と末尾が埋まった表を右に巡回シフトしてソートすると，先頭の次のカラムが決定できる．
 * これをナイーブに，各行をvectorで持ってソートするように実装すると O(N^3 log N)．
 * また，ソートのときは直前の順番と，巡回して先頭にくる数値だけ持っていれば良いことに気づくと O(N^2 log N) まで落とせる．
 *
 * しかし O(N^2 log N) ではまだTLEしてしまう．
 * ここで，毎回の巡回シフトで先頭に追加されるカラム列は毎回同じ(末尾のカラム)であることに注意すると，
 * 末尾はソート済みで先頭だけが非ソート済みのものをソートするのであるから，結局末尾カラムを安定ソートすることと等しく，
 * 毎回のソートで行われる置換はまったく同じであることが分かる．
 * したがってこの置換を求め，順にたどっていけば目的の列が得られる．
 *
 * 最終的なオーダーは O(N log N) でソートしたあと，各桁を決定するのに O(N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> digits(N);
    for(int i = 0; i < N; ++i) {
        cin >> digits[i];
    }

    vector<pair<int,int> > perm(N);
    for(int i = 0; i < N; ++i) {
        perm[i] = make_pair(digits[i], i);
    }
    sort(perm.begin(), perm.end());

    int pos = 0;
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << digits[perm[pos].second];
        pos = perm[pos].second;
    }
    cout << endl;

    return 0;
}
