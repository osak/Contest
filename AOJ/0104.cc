//Name: Magical Tiles
//Level: 2
//Category: 文字列,メモ化
//Note:

/**
 * 一度通った場所を覚えておきながら移動をシミュレーションする。
 * 同じ場所に2回来た場合、ループしている。
 *
 * オーダーは O(HW)。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool solve() {
    int H, W;
    cin >> H >> W;
    if(!H && !W) return false;

    vector<string> field(H);
    for(int i = 0; i < H; ++i) {
        cin >> field[i];
    }
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    int r = 0, c = 0;
    bool looped = false;
    while(true) {
        visited[r][c] = true;
        switch(field[r][c]) {
        case '>':
            c++;
            break;
        case '<':
            c--;
            break;
        case '^':
            r--;
            break;
        case 'v':
            r++;
            break;
        default:
            goto end;
        }
        if(visited[r][c]) {
            looped = true;
            break;
        }
    }
end:
    if(looped) cout << "LOOP" << endl;
    else cout << c << ' ' << r << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
