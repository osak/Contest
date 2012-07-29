#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace std;

typedef unsigned long long ULL;

string succ(const string &s) {
    int N = s.size();
    char buf[N+2];
    const int val = atoll(s.c_str());
    const int len = sprintf(buf, "%0*d", N, val+1);
    return string(buf);
}

string prev(const string &s) {
    int N = s.size();
    char buf[N+2];
    const int val = atoll(s.c_str());
    sprintf(buf, "%d", val-1);
    return string(buf);
}

bool test(const string &str, int pos, string val) {
    while(pos < str.size()) {
        int len = min(str.size()-pos, val.size());
        const string s1 = str.substr(pos, len);
        const string s2 = val.substr(0, len);
        if(s1 != s2) return false;
        pos += len;
        val = succ(val);
    }

    return true;
}

inline ULL mypow(int x, int a) {
    ULL res = 1;
    for(int i = 0; i < a; ++i) res *= x;
    return res;
}

ULL calc(const string &val) {
    int N = val.size();
    ULL res = 0;
    ULL ord = 1;
    for(int i = 1; i < N; ++i) {
        res += i * (ord*9);
        ord *= 10;
    }
    res += ((ULL)atoll(val.c_str())-ord)*N+1;
    //if(N > 1) --res;
    return res;
}

int main() {
    assert(succ("1") == "2");
    assert(succ("9") == "10");
    assert(succ("01") == "02");
    assert(succ("09") == "10");
    assert(succ("99") == "100");
    assert(prev("55") == "54");
    assert(prev("1") == "0");
    assert(prev("10") == "9");
    assert(test("12345", 0, "1"));
    assert(test("67891011", 0, "6"));
    assert(!test("67891012", 0, "6"));
    //cout << calc("123000124") << endl;

    while(true) {
        string str;
        cin >> str;
        if(str == "#") break;

        if(atoll(str.c_str()) == 0) str += "1";
        ULL ans = str.size() < 18 ? calc(str) : 10000000000000000;
        for(int len = 1; len < 18 && len < str.size(); ++len) {
            string suffix = str.substr(0, len);
            string next = succ(suffix);
            if(next.size() > len) next.erase(0);
            int pos = str.find(next, len);
            // suffixが0(と等価)なとき，prefillは一桁であってはいけない！
            if(atoll(suffix.c_str()) == 0 && pos != string::npos && len == pos) {
                pos = str.find(next, pos+1);
            }
            string prefill = "";
            if(pos != string::npos) {
                prefill = str.substr(len, pos-len);
                if(prefill[0] != '0' && test(str, len, prefill+next)) {
                    string target = prefill + suffix;
                    //cout << target << endl;
                    if(target.size() < 18) ans = min(ans, calc(target)+(target.size()-len));
                }
            }

            //後ろ全部をprefillにするのは常に可能
            prefill = str.substr(len);
            if(prefill.size() > 0 && prefill[0] != '0') {
                if(atoll(next.c_str()) == 0) {
                    prefill = prev(prefill);
                }

                string target = prefill + suffix;
                //cout << target << endl;
                if(target.size() < 18) ans = min(ans, calc(target)+(target.size()-len));
            }
        }
        cout << ans << endl;
    }
}
