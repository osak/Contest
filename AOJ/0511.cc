//Name: Who Are The Student Yet Submit
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<bool> v(30, false);
    for(int i = 0; i < 28; ++i) {
        int n;
        cin >> n;
        v[n-1] = true;
    }
    for(int i = 0; i < 30; ++i) {
        if(!v[i]) {
            cout << i+1 << endl;
        }
    }
    return 0;
}
