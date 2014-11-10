//Name: Total Time
//Level: 1
//Category: やるだけ
//Note:

/**
 * 秒数を全て足し、60で割った商と余りを出力する。
 */
#include <iostream>

using namespace std;

int main() {
    int sum = 0;
    for(int i = 0; i < 4; ++i) {
        int n;
        cin >> n;
        sum += n;
    }
    cout << sum / 60 << endl;
    cout << sum % 60 << endl;

    return 0;
}
