#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>

using namespace std;

int eval_fact(const string &exp, int &pos) {
    int val = 0;
    if(!isdigit(exp.at(pos)) || exp.at(pos) == '0') throw "invalid factor";
    while(pos < exp.size() && isdigit(exp.at(pos))) {
        val *= 10;
        val += exp.at(pos++)-'0';
    }
    return val;
}

int eval_term(const string &exp, int &pos) {
    int lhs = eval_fact(exp, pos);
    while(pos < exp.size()) {
        char op = exp.at(pos++);
        if(op == '*') {
            int rhs = eval_fact(exp, pos);
            lhs *= rhs;
        }
        else if(op == '/') {
            int rhs = eval_fact(exp, pos);
            if(rhs == 0 || lhs % rhs != 0) throw "invalid division";
            lhs /= rhs;
        }
        else {
            pos--;
            break;
        }
    }
    return lhs;
}

int eval_expression(const string &exp,int &pos) {
    int lhs = eval_term(exp, pos);
    while(pos < exp.size()) {
        char op = exp.at(pos++);
        if(op == '+') {
            int rhs = eval_term(exp, pos);
            lhs += rhs;
        }
        else if(op == '-') {
            int rhs = eval_term(exp, pos);
            lhs -= rhs;
        }
        else {
            pos--;
            break;
        }
    }
    return lhs;
}

int eval(const string &exp) {
    int pos = 0;
    if(exp.size() == 0) return 0;
    int val = eval_expression(exp, pos);
    if(pos != exp.size()) throw "invalid expression";
    return val;
}

bool check(const vector<string> &v) {
    bool ok = true;
    int H = v.size();
    for(int r = 0; r < H; ++r) {
        int start = 0;
        while(start < v[r].size()) {
            int bl = v[r].find('#', start);
            if(bl == string::npos) bl = v[r].size();
            string eq = v[r].substr(start, bl-start);
            int epos = eq.find('=');
            if(epos != string::npos) {
                string lhs = eq.substr(0, epos), rhs = eq.substr(epos+1);
                //cout << eq << '$' << lhs << ' ' << rhs << endl;
                try {
                    if(eval(lhs) != eval(rhs)) {
                        return false;
                        break;
                    }
                } catch (const char *str) {
                    return false;
                    break;
                }
            }
            start = bl+1;
        }
    }
    return true;
}

int main() {
    while(true) {
        int H, W;
        cin >> H >> W;
        if(!H && !W) break;

        vector<string> field(H);
        vector<pair<int,int> > space;
        for(int i = 0; i < H; ++i) {
            cin >> field[i];
            field[i] += '#';
            for(int j = 0; j < W; ++j)
                if(field[i][j] == '.') space.push_back(make_pair(i, j));
        }

        int N;
        cin >> N;
        vector<char> piece(N);
        for(int i = 0; i < N; ++i) cin >> piece[i];

        sort(piece.begin(), piece.end());
        bool hasans = false;
        do {
            vector<string> tmp = field;
            for(int i = 0; i < N; ++i) {
                pair<int,int> s = space[i];
                tmp[s.first][s.second] = piece[i];
            }
            if(!check(tmp)) continue;

            vector<string> tmpt(W);
            for(int r = 0; r < H; ++r) {
                for(int c = 0; c < W; ++c) {
                    tmpt[c] += tmp[r][c];
                }
            }
            for(int i = 0; i < tmpt.size(); ++i) tmpt[i] += '#';

            if(!check(tmpt)) continue;

            hasans = true;
            break;
        } while(next_permutation(piece.begin(), piece.end()));
        cout << (hasans?"Yes":"No") << endl;
    } 
    return 0;
}

