//Name: A Die Maker
//Level: 4
//Category: 辞書順最小,サイコロ
//Note:

/**
 * 辞書順最小の文字列を求める問題であるから、1回Eをやってゴールに到達可能ならE、さもなくばN……というように試していき、
 * 使った文字を並べればよい。
 * 以降、簡単のため、サイコロの各面の数をt_iから減らしていき、0にする問題だと考える。
 *
 * ゴールに到達可能かどうかの判定は、サイコロのある面の対面の数を増やすには、他の4面のいずれかを経由しなければならないことを用いる。
 * 接地面に隣り合っているある面について考えると、この面とその対面の数（それぞれa, bとする）を0にするには、他の4面を最低でもa+b-1回経由することになる。
 * したがって、ゴールへ到達可能な必要条件として、
 *   (1) a+b-1 ≦他の4面の合計
 * が存在する。接地面の場合は
 *   (2) a+b ≦ 他の4面の合計
 * である。
 * 逆に、全ての面の組み合わせがこれを満たしているときに1回サイコロを回転させると、新しく接地面になる面とその対に対しては、明らかに(2)を満たす。
 * 一方、回転前に接地面だった面も、(2)の両辺から1を引く（「他の4面の合計」が1だけ減っているため）ことで(1)を満たす。
 * 残りの面については(1)を満たさなくなる可能性があるが、回転前で接地していない2組の面が、両方とも等号で(1)が成立することはない。
 * （もしも等号で成立すると、接地面の組の和をkとして a+b-1 = k+c+d, c+d-1 = k+a+b より k=-1 となり、kの非負性に反する）
 * したがって、必要条件を保ったままで回転する方法が存在する。
 *
 * 以上より、次のようにすればよい。
 * ・初期状態が条件を満たしていない場合、そのサイコロは作成不可能である。
 * ・初期状態が条件を満たしている場合、E, N, S, Wを順に試し、転がせる最初の方向に転がす。
 * 　サイコロへの面の付け方を全て試し、辞書順最小の文字列が得られるものを採用する。
 *
 * オーダーは O(Σt_i)。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <array>
#include <cassert>

using namespace std;

//  4
// 0123
//  5
// 5番の面が接地しており、1が手前に見えている。
const int ROT[6][6] = {
    {5, 1, 4, 3, 0, 2}, // E
    {0, 5, 2, 4, 1, 3}, // N
    {0, 4, 2, 5, 3, 1}, // S
    {4, 1, 5, 3, 2, 0}, // W
    {1, 2, 3, 0, 4, 5}, // CW
    {3, 0, 1, 2, 4, 5}  // CCW
};
const string DIRC = "ENSW";

void rotate(int dir, const vector<int> &org, vector<int> &out) {
    for(int i = 0; i < 6; ++i) {
        out[i] = org[ROT[dir][i]];
    }
}

bool check(const vector<int> &d) {
    return (d[0]+d[2]-1 <= d[1]+d[3]+d[4]+d[5]) &&
           (d[1]+d[3]-1 <= d[0]+d[2]+d[4]+d[5]) &&
           (d[4]+d[5] <= d[0]+d[1]+d[2]+d[3]);
}

bool solve() {
    vector<int> d(6);
    int sum = 0;
    for(int i = 0; i < 6; ++i) {
        cin >> d[i];
        sum += d[i];
    }
    if(sum == 0) return false;

    int p, q;
    cin >> p >> q;
    --p; --q;

    string res = "";
    sort(begin(d), end(d));
    do {
        if(!check(d)) {
            continue;
        }
        string str;
        vector<int> v = d, tmp(6);
        int rem = sum;
        while(rem) {
            /*
            for(int i = 0; i < 6; ++i) {
                cout << d[i] << ' ' ;
            }
            cout << endl;
            */
            for(int i = 0; i < 4; ++i) {
                rotate(i, v, tmp);
                if(tmp[5] > 0) {
                    tmp[5]--;
                    /*
                    for(int j = 0; j < 6; ++j) {
                        cout << v[j] << ' ' ;
                    }
                    cout << endl;
                    */
                    if(check(tmp)) {
                        str += DIRC[i];
                        v.swap(tmp);
                        break;
                    }
                }
                if(i == 3) assert(false);
            }
            rem--;
        }
        if(res == "" || res > str) res = str;
    } while(next_permutation(begin(d), end(d)));
    if(res == "") {
        cout << "impossible" << endl;
    } else {
        for(int i = p; i <= q; ++i) {
            cout << res[i];
        }
        cout << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
