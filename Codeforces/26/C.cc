#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, m, a, b, c;
    cin >> n >> m >> a >> b >> c;

    vector<vector<int> > field(n, vector<int>(m, 0));
    int rem = n*m;

    if(n*m % 2 == 1) goto IMPOSSIBLE;
    if(n*m > 2*a + 2*b + 4*c) goto IMPOSSIBLE;

    if(n % 2 == 1) {
        for(int i = 0; i < m; i += 2) {
            if(a == 0) goto IMPOSSIBLE;
            --a;
            field[n-1][i] = field[n-1][i+1] = (i%4)+10;
        }
        --n;
        rem -= m;
    }
    else if(m % 2 == 1) {
        for(int i = 0; i < n; i += 2) {
            if(b == 0) goto IMPOSSIBLE;
            --b;
            field[i][m-1] = field[i+1][m-1] = (i%4)+10;
        }
        --m;
        rem -= n;
    }
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(field[i][j] != 0) continue;
            vector<bool> used(10, false);
            if(i > 0) used[field[i-1][j]] = true;
            if(i > 0 && j < m-1) used[field[i-1][j+1]] = true;
            if(j > 0) used[field[i][j-1]] = true;
            if(i < n-1 && j > 0) used[field[i+1][j-1]] = true;
            
            int pos = 1;
            int num1, num2;
            while(used[pos]) ++pos;
            num1 = pos++;
            while(used[pos]) ++pos;
            num2 = pos;

            if(b >= 2) {
                field[i][j] = field[i+1][j] = num1;
                field[i][j+1] = field[i+1][j+1] = num2;
                b -= 2;
            }
            else if(a >= 2) {
                field[i][j] = field[i][j+1] = num1;
                field[i+1][j] = field[i+1][j+1] = num2;
                a -= 2;
            }
            else if(c >= 1) {
                field[i][j] = field[i][j+1] = field[i+1][j] = field[i+1][j+1] = num1;
                c -= 1;
            }
            else goto IMPOSSIBLE;
        }
    }

    for(int i = 0; i < field.size(); ++i) {
        for(int j = 0; j < field[i].size(); ++j) {
            cout << char('a'+field[i][j]);
        }
        cout << endl;
    }
    goto END;

IMPOSSIBLE:
    cout << "IMPOSSIBLE" << endl;

END:
    return 0;
}
