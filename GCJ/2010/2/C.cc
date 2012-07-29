#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

void print_field(const vector<vector<bool> > &field, int size) {
    for(int y = 0; y <= size; ++y) {
        for(int x = 0; x <= size; ++x) {
            cerr << field[x][y] << " ";
        }
        cerr << endl;
    }
}

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int n;
        cin >> n;
        vector<vector<bool> > field(100, vector<bool>(100, false));
        vector<vector<bool> > field_tmp(100, vector<bool>(100, false));

        int left, right, top, bottom;
        right = bottom = 0;
        left = top = 101;
        for(int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;
            for(int x = x1; x <= x2; ++x) {
                for(int y = y1; y <= y2; ++y) {
                    field[x][y] = true;
                }
            }
            left = min(left, x1);
            right = max(right, x2);
            top = min(top, y1);
            bottom = max(bottom, y2);
        }

        int cnt = 0;
        bool end = false;
        while(!end) {
            /*
            if(cnt < 10) {
                print_field(field, max(right, bottom));
                cerr << endl;
            }
            */
            end = true;
            for(int x = left; x <= right; ++x) {
                for(int y = top; y <= bottom; ++y) {
                    if(y>0 && x>0 && field[x][y-1] && field[x-1][y]) {
                        field_tmp[x][y] = true;
                        end = false;
                    }
                    else if(!(y>0 && field[x][y-1]) && !(x>0 && field[x-1][y])) {
                        field_tmp[x][y] = false;
                    }
                    else {
                        if(field_tmp[x][y] = field[x][y]) end = false;
                    }
                }
            }
            ++cnt;
            field = field_tmp;
        }
        cout << "Case #" << C << ": " << cnt << endl;
    }
    return 0;
}
