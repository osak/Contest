//Name: Book Index
//Level: 2
//Category: やるだけ
//Note:

/**
 * mapを使って語句とページ番号を管理すると、語句は勝手に昇順に並ぶ。
 * ページ番号は出力時にソートする。
 *
 * オーダーは O(N|S| log N)。
 * ただしNは語句の個数、|S|は語句の最大長。
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool solve() {
    string word;
    int page;
    map<string,vector<int>> dict;
    while(cin >> word >> page) {
        dict[word].push_back(page);
    }
    for(auto &e : dict) {
        cout << e.first << endl;
        sort(begin(e.second), end(e.second));
        for(int i = 0; i < (int)e.second.size(); ++i) {
            if(i > 0) cout << ' ';
            cout << e.second[i];
        }
        cout << endl;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
