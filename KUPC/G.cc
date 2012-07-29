#include <iostream>
#include <set>
#include <cstdlib>

using namespace std;

void print_it(const set<int> &s, int n) {
    cout << '?';
    for(int i = 0; i < n; ++i)
        cout << s.count(i);
    cout << endl;
    cout << flush;
}

int getval() {
    int i;
    cin >> i;
    return i;
}

void divide(set<int> &s1, set<int> &s2) {
    int left = s1.size() / 2;

    s2.clear();
    for(set<int>::iterator it = s1.begin(); left && it != s1.end(); --left) {
        s2.insert(*it);
        s1.erase(it++);
    }
}

void generate(set<int> &s, const set<int> &blacklist, int n) {
    do {
        s.clear();
        for(int i = 0; i < n; ++i)
            if(blacklist.count(i) == 0 && rand() % 2) s.insert(i);
    } while(s.size() == 0);
}

int main() {
    int N, K;
    cin >> N >> K;

    srand(time(NULL));

    set<int> ans;
    for(int i = 0; i < K; ++i) {
        set<int> s;
        do {
            generate(s, ans, N);
            print_it(s, N);
        } while(getval() == 0);

        while(s.size() > 1) {
            set<int> tmp;
            divide(s, tmp);
            print_it(s, N);
            if(getval() == 0) s = tmp;
        }
        ans.insert(*s.begin());
    }

    bool first = true;
    cout << '!';
    for(set<int>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
        if(!first) cout << ' ';
        cout << *it+1;
        first = false;
    }
    cout << endl;

    return 0;
}
