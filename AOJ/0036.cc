//Name: A Figure on Surface
//Level: 1
//Category: シミュレーション,場合分け
//Note:

/*
 * 図形が重なっていることはないので、端点を見つけたら全ての可能性を試す。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool one(const vector<string> &v, int x, int y) {
    if(x < 0 || y < 0 || x >= v[0].size() || y >= v.size()) return false;
    return v[y][x] == '1';
}

int main() {
    vector<string> v(8);
    while(cin >> v[0]) {
        for(int i = 1; i < 8; ++i) cin >> v[i];

        char kind;
        for(int y = 0; y < 8; ++y) {
            for(int x = 0; x < 8; ++x) {
                if(one(v, x, y)) {
                    if(one(v, x+1, y) && one(v, x, y+1) && one(v, x+1, y+1)) kind = 'A';
                    else if(one(v, x, y+1) && one(v, x, y+2) && one(v, x, y+3)) kind = 'B';
                    else if(one(v, x+1, y) && one(v, x+2, y) && one(v, x+3, y)) kind = 'C';
                    else if(one(v, x, y+1) && one(v, x-1, y+1) && one(v, x-1, y+2)) kind = 'D';
                    else if(one(v, x+1, y) && one(v, x+1, y+1) && one(v, x+2, y+1)) kind = 'E';
                    else if(one(v, x, y+1) && one(v, x+1, y+1) && one(v, x+1, y+2)) kind = 'F';
                    else if(one(v, x+1, y) && one(v, x, y+1) && one(v, x-1, y+1)) kind = 'G';
                    goto end;
                }
            }
        }
end:
        cout << kind << endl;
    }
    return 0;
}
