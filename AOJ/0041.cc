//Name: Expression
//Level: 3
//Category: 全探索,数式
//Note:

/*
 * 後置記法で構成した数式を全探索する。
 */

#include <iostream>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

const char *opchr = "+-*";

int eval(int lhs, int op, int rhs) {
    switch(op) {
        case 0: return lhs+rhs;
        case 1: return lhs-rhs;
        case 2: return lhs*rhs;
    }
    return 0;
}

int main() {
    while(true) {
        int ns[4];
        for(int i = 0; i < 4; ++i) cin >> ns[i];
        if(!ns[0] && !ns[1] && !ns[2] && !ns[3]) break;

        sort(ns, ns+4);
        do {
            for(int pat = 0; pat < 27; ++pat) {
                int oppos[6] = {0};
                oppos[3] = oppos[4] = oppos[5] = 1;
                do {
                    int opn = 0;
                    int div = 1;
                    stack<int> s;
                    stack<string> hist;
                    for(int i = 0; i < 4; ++i) {
                        s.push(ns[i]);
                        string numstr;
                        numstr += ns[i]+'0';
                        hist.push(numstr);
                        for(int j = 0; j < i; ++j)
                            if(oppos[opn+j]) {
                                if(s.size() < 2) goto next_patperm;
                                int lhs = s.top(); s.pop();
                                int rhs = s.top(); s.pop();
                                s.push(eval(lhs, pat/div%3, rhs));
                                string lhse = hist.top(); hist.pop();
                                string rhse = hist.top(); hist.pop();
                                hist.push("(" + lhse + opchr[pat/div%3] + rhse + ")");
                                div *= 3;
                            }
                        opn += i;
                    }
                    if(s.top() == 10) {
                        cout << hist.top() << endl;
                        goto next;
                    }
next_patperm:
                    ;
                } while(next_permutation(oppos, oppos+6));
            }
        } while(next_permutation(ns, ns+4));
        cout << 0 << endl;
next:
        ;
    }
    return 0;
}
