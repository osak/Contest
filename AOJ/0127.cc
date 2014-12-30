//Name: Pocket Pager Input
//Level: 1
//Category: 文字列
//Note: 

/**
 * 表を引くだけ。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve(bool first) {
    static const char tbl[6][6] = {
        "abcde",
        "fghij",
        "klmno",
        "pqrst",
        "uvwxy",
        "z.?! "
    };

    string line;
    if(!getline(cin, line)) return false;
    if(line.size() % 2 == 1) {
        cout << "NA" << endl;
        return true;
    }
    string buf;
    for(int i = 0; i < line.size(); i += 2) {
        const int r = line[i] - '0' - 1;
        const int c = line[i+1] - '0' - 1;
        if(r < 0 || r >= 6 || c < 0 || c >= 5) {
            cout << "NA" << endl;
            return true;
        }
        buf += tbl[r][c];
    }
    cout << buf << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
