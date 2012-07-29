#include <iostream>

using namespace std;

int main() {
    for(int i = 0; i < 3; ++i) {
        int h1,m1,s1,h2,m2,s2;
        cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
        if(s2 < s1) {
            --m2;
            s2 += 60;
        }
        s2 -= s1;
        if(m2 < m1) {
            --h2;
            m2 += 60;
        }
        m2 -= m1;
        h2 -= h1;
        cout << h2 << ' ' << m2 << ' ' << s2 << endl;
    }
    return 0;
}
