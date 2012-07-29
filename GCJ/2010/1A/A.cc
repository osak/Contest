#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

void print_field(vector<string> &field) {
    for(int i = 0; i < field.size(); ++i) {
        cout << field[i] << endl;
    }
}

vector<string> rotate(vector<string> field, int times) {
    vector<string> newfield(field.size(), "");
    for(int n = 0; n < times; ++n) {
        newfield.clear();
        newfield.resize(field.size(), "");
        for(int i = 0; i < field.size(); ++i) {
            for(int j = 0; j < field[i].size(); ++j) {
                newfield[i] += field[field[i].size()-j-1][i];
            }
        }

        field = newfield;
    }

    for(int y = newfield.size()-1; y >= 0; --y) {
        for(int x = 0; x < field[y].size(); ++x) {
            if(newfield[y][x] != '.') {
                int curry = y;
                while(curry+1 <= newfield.size()-1 && newfield[curry+1][x] == '.') {
                    newfield[curry+1][x] = newfield[curry][x];
                    newfield[curry][x] = '.';
                    ++curry;
                }
            }
        }
    }

    return newfield;
}

bool checkwin(vector<string> field, int cnt, char c) {
    vector<int> tatecnt(field.size(), 0);
    vector<vector<int> > nanamecnt(field.size(), vector<int>(field.size(), 0));
    vector<vector<int> > nanamecnt_r(field.size(), vector<int>(field.size(), 0));

    for(int y = 0; y < field.size(); ++y) {
        int yokocnt = 0;
        for(int x = 0; x < field[y].size(); ++x) {
            if(field[y][x] == c) {
                ++yokocnt;
                ++tatecnt[x];
                if(y > 0 && x > 0) {
                    nanamecnt[y][x] = nanamecnt[y-1][x-1]+1;
                }
                else nanamecnt[y][x]++;
                if(y > 0 && x+1 < field.size()) {
                    nanamecnt_r[y][x] = nanamecnt_r[y-1][x+1]+1;
                }
                else nanamecnt_r[y][x]++;
            }
            else {
                yokocnt = tatecnt[x] = 0;
            }
            if(yokocnt >= cnt) return true;
            if(tatecnt[x] >= cnt) return true;
            if(nanamecnt[y][x] >= cnt) return true;
            if(nanamecnt_r[y][x] >= cnt) return true;
        }
    }

endloop: 
    for(int i = 0; i < tatecnt.size(); ++i) {
        if(tatecnt[i] >= cnt) return true;
    }
    for(int i = 0; i < field.size(); ++i) {
        if(nanamecnt[field.size()-1][i] >= cnt) return true;
        if(nanamecnt_r[field.size()-1][i] >= cnt) return true;
    }
    return false;
}

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int N, K;
        cin >> N >> K;

        vector<string> field;
        for(int i = 0; i < N; ++i) {
            string str;
            cin >> str;
            field.push_back(str);
        }

        vector<string> newfield = rotate(field, 1);
//        cout << K << endl;
//        print_field(newfield);
        int win = 0;
        if(checkwin(newfield, K, 'R')) win |= 1;
        if(checkwin(newfield, K, 'B')) win |= 2;

        char winstr[][80] = {"Neither", "Red", "Blue", "Both"};
        printf("Case #%d: %s\n", C, winstr[win]);
    }
}
