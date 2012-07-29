#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

string tags[10001];
int nums[100001];
bool res[100001];
map<string, vector<int> >m;

void parse(string s, string &tag, int &num, bool &re) {
    int pos = s.size()-1;
    if (s[pos] == 'v') {
        re = true;
        pos--;
    } else {
        re = false;
    }

    if (s[pos] == '-' && pos == 0) {
        tag = "";
        num = 0;
        return;
    }

    while (isdigit(s[pos])) {
        pos--;
    }
    int npos = pos+1;
    num = 0;
    while (isdigit(s[npos]) && npos < s.size()) {
        num *= 10;
        num += s[npos] - '0';
        npos++;
    }

    tag = s.substr(0, pos+1);
}

void show(int line_num) {
    cout << line_num << endl;
    if (res[line_num]) {
        show(line_num-1);
    }

    if (tags[line_num] != "" && nums[line_num] != 0 && m.find(tags[line_num]) != m.end()) {
        int n = m[tags[line_num]].back();
        m[tags[line_num]].pop_back();
        if (m[tags[line_num]].empty()) {
            m.erase(m.find(tags[line_num]));
        }
        show(n);
    }
}

int main(void) {
    int N;
    for (;;) {
        cin >> N;
        if (N == 0) break;
        for (int line_num = 1; line_num <= N; line_num++) {
            string s;
            cin >> s;
            string tag;
            int num;
            bool re;
            parse(s, tag, num, re);

            res[line_num+1] = re;

            tags[line_num] = tag;
            nums[line_num] = num;
            if (num >= 2) {
                if (m.find(tag) == m.end()) {
                    vector<int> v;
                    v.push_back(line_num);
                    m[tag] = v;
                } else {
                    m[tag].push_back(line_num);
                }
            }

            if (!re && ((tag != "" && num == 1) || tag == "")) {
                show(line_num);
            }
        }
    }
    return 0;
}
