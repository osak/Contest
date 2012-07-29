#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
  while(true) {
    string str;
    getline(cin, str);
    if(str == ".") break;

    stack<char> st;
    int maru, kado;
    bool valid = true;
    maru = kado = 0;
    for(int i = 0; i < str.size(); ++i) {
      switch(str[i]) {
        case '(':
          st.push('(');
          break;
        case ')':
          if(st.empty() || st.top() != '(') valid = false;
          if(!st.empty()) st.pop();
          break;
        case '[':
          st.push('[');
          break;
        case ']':
          if(st.empty() || st.top() != '[') valid = false;
          if(!st.empty()) st.pop();
          break;
      }
    }

    if(!st.empty()) valid = false;
    cout << (valid?"yes":"no") << endl;
  }
  return 0;
}
