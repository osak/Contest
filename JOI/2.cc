#include <iostream>
#include <string>

using namespace std;

int main() {
    string t;
    cin >> t;
    int N;
    cin >> N;
    int cnt = 0;
    while(N--) {
        string s;
        cin >> s;
        s += s;
        if(s.find(t) != string::npos) ++cnt;
    }
    cout << cnt << endl;

    return 0;
}
