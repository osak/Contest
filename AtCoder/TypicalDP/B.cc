//Name: ゲーム
//Level: 3
//Category: DP,動的計画法,ゲーム木探索
//Note: Typical DP Contest B

/*
 * 各ターンでは左の山から取るか、右の山から取るかの2択。
 * それぞれのパターンを読み切り、もっとも自分の点数が高くなる手を選択する。
 *
 * 状態は2つの山の残り枚数の組（どちらの手番かは山の残り枚数から一意に定まる）。
 * この各状態について、メモ化が可能である。
 *
 * オーダーはO(AB)。
 */
#include <iostream>
#include <vector>

using namespace std;

struct Tag {
    int score[2];
    bool valid;

    Tag() : valid(false){score[0] = score[1] = 0;}
};

Tag memo[1001][1001];
vector<int> pile[2];

Tag calc(vector<int> &pos, int turn) {
    Tag &tag = memo[pos[0]][pos[1]];
    if(tag.valid) {
        return tag;
    }

    for(int which = 0; which <= 1; ++which) {
        if(pos[which] < pile[which].size()) {
            pos[which]++;
            Tag tmp = calc(pos, 1-turn);
            pos[which]--;
            tmp.score[turn] += pile[which][pos[which]];
            if(tmp.score[turn] > tag.score[turn]) {
                tag = tmp;
            }
        }
    }
    tag.valid = true;
    return tag;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int A, B;
    cin >> A >> B;
    pile[0].resize(A);
    pile[1].resize(B);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < pile[i].size(); ++j) {
            cin >> pile[i][j];
        }
    }
    vector<int> pos(2);
    pos[0] = 0;
    pos[1] = 0;
    cout << calc(pos, 0).score[0] << endl;
    return 0;
}
