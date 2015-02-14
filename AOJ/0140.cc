//Name: Bus Line
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * 1周ぶんの系列を埋め込んでおき、適宜出力する。
 * 直線部のバス停が指定された時は別途対応する。
 */
#include <iostream>
#include <vector>

using namespace std;

const int ROUTE[] = {
    0,1,2,3,4,5,6,7,8,9,5,4,3,2,1
};

bool solve(bool first) {
    int a, b;
    cin >> a >> b;
    if(a <= 5 && b <= 5) {
        bool first = true;
        for(int i = a; i != b; i += a<b?1:-1) {
            if(!first) cout << ' ';
            cout << i;
            first = false;
        }
        cout << ' ' << b;
    } else {
        int cur = 0;
        while(ROUTE[cur] != a) ++cur;
        cout << ROUTE[cur];
        while(ROUTE[cur] != b) {
            cur = (cur + 1) % (sizeof(ROUTE) / sizeof(int));
            cout << ' ' << ROUTE[cur];
        }
    }
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
