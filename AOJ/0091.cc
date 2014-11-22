//Name: Blur
//Level: 3
//Category: 探索
//Note:

/**
 * フィールドを左上から右下に向けて、Y-major orderで走査していく。
 * この順で走査すると、最初に見つかる色の付いているマスは、以下の3パターンのどれかで着色されている。
 * ・(x, y+1)に小が落ちた
 * ・(x+1, y+1)に中が落ちた
 * ・(x, y+2)に大が落ちた
 * この全てのパターンを試しながら走査を繰り返し、矛盾が生じないように置けたものを採用すればよい。
 *
 * 状態数としては、染料の数Nについて、深さNの3分木のもつノード数が上限となる。
 * したがって、見なければならない状態数は高々 3^(N+1) であり、オーダーは O(3^N)。
 */
#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct Drop {
    int x, y, size;
};

array<array<int,10>, 10> field;
int N;

int MASK[3][5][5] = {
    {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
    },
    {
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,1,1,1,0},
        {0,1,1,1,0},
        {0,0,0,0,0},
    },
    {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0},
    }
};

int apply(int r, int c, int idx, int val) {
    if(idx == 0) {
        r -= 1;
        c -= 2;
    } else if(idx == 1) {
        r -= 1;
        c -= 1;
    } else if(idx == 2) {
        c -= 2;
    }
    bool valid = true;
    int cnt = 0;
    for(int dr = 0; dr < 5; ++dr) {
        for(int dc = 0; dc < 5; ++dc) {
            if(MASK[idx][dr][dc] == 1 && (r+dr < 0 || r+dr >= 10 || c+dc < 0 || c+dc >= 10)) {
                valid = false;
            } else {
                field[r+dr][c+dc] += val * MASK[idx][dr][dc];
                if(MASK[idx][dr][dc]) cnt++;
                if(field[r+dr][c+dc] < 0) valid = false;
            }
        }
    }
    return valid ? cnt : 0;
}

bool search(int r, int c, vector<Drop> &ans, int rem) {
    if(rem == 0) {
        if(ans.size() == N) return true;
        else return false;
    }
    if(ans.size() == N) {
        return rem == 0;
    }
    if(c == 10) {
        if(r == 9) return false;
        return search(r+1, 0, ans, rem);
    }
    if(field[r][c] == 0) {
        return search(r, c+1, ans, rem);
    }

    for(int i = 0; i < 3; ++i) {
        //cout << "try " << i << " on " << r << ' ' << c << endl;
        int cnt = apply(r, c, i, -1);
        if(cnt) {
            Drop d;
            switch(i) {
                case 0:
                    d = Drop{c, r+1, i+1};
                    break;
                case 1:
                    d = Drop{c+1, r+1, i+1};
                    break;
                case 2:
                    d = Drop{c, r+2, i+1};
                    break;
            }
            ans.push_back(d);
            if(search(r, c, ans, rem - cnt)) return true;
            ans.pop_back();
        }
        apply(r, c, i, 1);
    }
    return false;
}

bool solve() {
    if(!(cin >> N)) return false;
    if(!N) return false;
    int sum = 0;
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            cin >> field[i][j];
            sum += field[i][j];
        }
    }
    vector<Drop> ans;
    search(0, 0, ans, sum);
    for(const Drop &d : ans) {
        cout << d.x << ' ' << d.y << ' ' << d.size << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
