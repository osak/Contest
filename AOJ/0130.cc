//Name: Train
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * stringでシミュレーションする。
 *
 * オーダーは O(|S|^2)。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve(bool first) {
    string s;
    cin >> s;

    string res;
    res += s[0];
    string::iterator it = begin(res);
    for(int i = 2; i < s.size(); i += 3) {
        bool top = false;
        if(s[i] == '>') {
            ++it;
        } else if(s[i] == '-') {
            if(it == begin(res)) top = true;
            else --it;
        }
        if(top || it == end(res)) {
            it = res.insert(it, s[i+1]);
        }
    }
    cout << res << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
