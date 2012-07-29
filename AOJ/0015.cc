#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        string s1, s2;
        cin >> s1 >> s2;

        if(s1.size() > 80 || s2.size() > 80) {
            cout << "overflow" << endl;
            continue;
        }
        char buf[81] = {0};
        int p1 = s1.size()-1, p2 = s2.size()-1, pb = 79;
        int carry = 0;
        while(p2 >= 0) buf[pb--] = s2[p2--];
        pb = 79;
        while(pb >= 0 && (p1 >= 0 || carry > 0)) {
            int bd = buf[pb];
            if(bd > 0) bd -= '0';
            int bp = 0;
            if(p1 >= 0) bp = s1[p1--]-'0';
            int d = bp + bd + carry;
            carry = d / 10;
            d %= 10;
            buf[pb--] = d+'0';
        }
        while(pb >= 0 && buf[pb]) pb--;
        if(pb == -1 && carry > 0) cout << "overflow" << endl;
        else cout << (char*)(buf+(pb+1)) << endl;
    }
    return 0;
}
