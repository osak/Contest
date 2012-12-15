//Name: Era Name Transformation
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

const int key[] = {
    18680907, 19120729, 19261224, 19890107
};
const string era[] = {
    "pre-meiji", "meiji", "taisho", "showa", "heisei"
};
const int offset[] = {
    0, 1868, 1912, 1926, 1989
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int Y, M, D;
    while(cin >> Y >> M >> D) {
        int v = Y*10000 + M * 100 + D;
        int pos = 0;
        while(pos < 4 && key[pos] < v) ++pos;
        if(pos == 0) {
            cout << era[pos] << endl;
        } else {
            cout << era[pos] << ' ' << Y-offset[pos]+1 << ' ' << M << ' ' << D << endl;
        }
    }
    return 0;
}
