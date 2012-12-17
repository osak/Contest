//Name: Strange Mathematical Expression
//Level: 1
//Category: 逆ポーランド記法,やるだけ
//Note:

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cstdio>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string line;
    while(getline(cin, line) && !cin.eof()) {
        istringstream is(line);
        stack<double> stk;
        string token;
        while(is >> token) {
            if(isdigit(token[0]) || token.size() >= 2) {
                stk.push(atof(token.c_str()));
            } else {
                double b = stk.top(); stk.pop();
                double a = stk.top(); stk.pop();
                switch(token[0]) {
                    case '+':
                        stk.push(a+b);
                        break;
                    case '-':
                        stk.push(a-b);
                        break;
                    case '*':
                        stk.push(a*b);
                        break;
                    case '/':
                        stk.push(a/b);
                        break;
                }
            }
        }
        printf("%.10f\n", stk.top());
    }
    return 0;
}
