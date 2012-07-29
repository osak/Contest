#include <iostream>
#include <string>
#include <vector>

using namespace std;

void normalize(string &str) {
    int pos = 0;
    const int N = str.size();
    while(pos < N && str[pos] != '(') ++pos;
    if(pos == N) return;

    int paren_pos = pos;
    ++pos;
    while(str[pos] != ')') {
        if(str[pos] != '9') return;
        ++pos;
    }

    // all 9
    str.erase(str.begin()+paren_pos);
    pos = paren_pos-1;
    while(str[pos] == '9') --pos;
    str[pos] += 1;
    str.erase(str.begin()+pos+1);
}

int loop_len(const string &a, int start) {
    int len = 0, pos = start;
    while(a[pos++] != ')') ++len;
    return len-1;
}

// a[pos] == '(' とする．
bool check_after_loop(const string &a, const string &b, int pos) {
    int a_loop_start = pos+1, b_loop_start = -1;
    int apos = pos+1, bpos = pos;
    const int BLEN = b.size();

    while(bpos < BLEN && b[bpos] != '(') {
        if(a[apos] != b[bpos]) return false;
        if(a[++apos] == ')') apos = a_loop_start;
        ++bpos;
    }
    // infinite vs finite
    if(bpos == BLEN) return false;

    b_loop_start = ++bpos;
    int a_len = loop_len(a, a_loop_start);
    int b_len = loop_len(b, b_loop_start);
    bool seen[300] = {0};
    while(!seen[apos]) {
        bpos = b_loop_start;
        for(int i = 0; i < b_len; ++i, ++bpos) {
            if(a[apos] != b[bpos]) return false;
            if(a[++apos] == '(') apos = a_loop_start;
        }
        seen[apos] = true;
    }

    return true;
}

bool check(const string &a, const string &b) {
    // (の出現までは一緒でないといけない
    // (9)は正規化済みとする
    int pos = 0;
    const int ALEN = a.size(), BLEN = b.size();
    while(pos < ALEN && pos < BLEN) {
        if(a[pos] != b[pos]) {
            if(a[pos] != '(' && b[pos] != '(') return false;
            break;
        }
        ++pos;
    }
    if(pos == ALEN || pos == BLEN) {
        return (pos == ALEN && pos == BLEN);
    }
    if(a[pos] == '(') return check_after_loop(a, b, pos);
    else if(b[pos] == '(') return check_after_loop(b, a, pos);
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<string> strs;
    while(N--) {
        string str;
        cin >> str;
        normalize(str);
        bool found = false;
        for(vector<string>::iterator it = strs.begin(); it != strs.end(); ++it) {
            if(check(str, *it)) {
                found = true;
                break;
            }
        }
        if(!found) strs.push_back(str);
    }

    cout << strs.size() << endl;
    return 0;
}
