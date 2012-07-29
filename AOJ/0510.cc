//Name: Score
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a = 0, b = 0;
    for(int i = 0; i < 4; ++i) {
        int n;
        cin >> n;
        a += n;
    }
    for(int i = 0; i < 4; ++i) {
        int n;
        cin >> n;
        b += n;
    }
    cout << max(a, b) << endl;
    return 0;
}
