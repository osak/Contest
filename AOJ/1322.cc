//Name: ASCII Expression
//Level: 4
//Category: 構文解析,実装
//Note:

/**
 * 毎回baseの位置を計算しながら、BNFの通りに構文解析する。
 * カッコを含めて演算子の前後には必ず空白が置いてあるため、先読みは1列だけで済む。
 *
 * オーダーは O(N^2 R)？
 */
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cassert>

using namespace std;

const int MOD = 2011;

array<int, 2011> inv;

void init() {
    for(int i = 0; i < MOD; ++i) {
        for(int j = 1; j < MOD; ++j) {
            if(i * j % MOD == 1) {
                inv[i] = j;
                break;
            }
        }
    }
}

vector<string> input;

int base_row(int r, int c, int er, int ec) {
    for(int i = r; i < er; ++i) {
        if(input[i][c] != '.') return i;
    }
    cerr << "Empty column: " << c << endl;
    assert(false);
}

void skip_white(int r, int &c, int er, int ec) {
    while(true) {
        for(int i = r; i < er; ++i) {
            if(input[i][c] != '.') return;
        }
        ++c;
    }
}

int term(int r, int &c, int er, int ec);
int factor(int r, int &c, int er, int ec);
int powexpr(int r, int &c, int er, int ec);
int primary(int r, int &c, int er, int ec);
int fraction(int r, int &c, int er, int ec);
int digit(int r, int c);

int expr(int r, int &c, int er, int ec) {
    skip_white(r, c, er, ec);
    const int base = base_row(r, c, er, ec);
    int lhs = term(r, c, er, ec);
    while(c < ec) {
        while(input[base][c] == '.') ++c;
        const char op = input[base][c];
        int rhs;
        switch(op) {
            case '+':
                ++c;
                rhs = term(r, c, er, ec);
                lhs += rhs;
                lhs %= MOD;
                break;
            case '-':
                ++c;
                rhs = term(r, c, er, ec);
                lhs -= rhs;
                while(lhs < 0) lhs += MOD;
                break;
            default:
                return lhs;
        }
    }
    return lhs;
}

int term(int r, int &c, int er, int ec) {
    skip_white(r, c, er, ec);
    const int base = base_row(r, c, er, ec);
    int lhs = factor(r, c, er, ec);
    while(c < ec) {
        while(input[base][c] == '.') ++c;
        const char op = input[base][c];
        int rhs;
        switch(op) {
            case '*':
                ++c;
                rhs = factor(r, c, er, ec);
                lhs *= rhs;
                lhs %= MOD;
                break;
            default:
                return lhs;
        }
    }
    return lhs;
}

int factor(int r, int &c, int er, int ec) {
    skip_white(r, c, er, ec);
    const int base = base_row(r, c, er, ec);
    if(input[base][c] == '-') {
        if(input[base][c+1] == '.') { // negate
            c += 2;
            const int f = factor(r, c, er, ec);
            //cout << f << ' ' << c << endl;
            return MOD - f;
        } else if(input[base][c+1] == '-') { // fraction
            return fraction(r, c, er, ec);
        } else {
            cerr << "Unknown factor at " << r << ' ' << c << ' ' << base << endl;
            assert(false);
        }
    } else if(isdigit(input[base][c]) || input[base][c] == '(') { // powexpr
        return powexpr(r, c, er, ec);
    } else {
        cerr << "Unknown factor at " << r << ' ' << c << ' ' << base << endl;
        assert(false);
    }
}

int fraction(int r, int &c, int er, int ec) {
    const int base = base_row(r, c, er, ec);
    int fec = c;
    while(fec < ec && input[base][fec] == '-') ++fec;
    int nc = c+1;
    const int num = expr(r, nc, base, fec-1);
    nc = c+1;
    const int den = expr(base+1, nc, er, fec-1);
    c = fec;
    return num * inv[den] % MOD;
}

int powexpr(int r, int &c, int er, int ec) {
    const int base = base_row(r, c, er, ec);
    const int n = primary(r, c, er, ec);
    if(base > r && c < ec && input[base-1][c] != '.') {
        const int x = digit(base-1, c);
        //cerr << n << ' ' << x << ' ' << c << endl;
        ++c; // skip digit
        int res = 1;
        for(int i = 0; i < x; ++i) {
            res *= n;
            res %= MOD;
        }
        return res;
    } else {
        return n;
    }
}

int primary(int r, int &c, int er, int ec) {
    const int base = base_row(r, c, er, ec);
    if(input[base][c] == '(') { // expr
        ++c; // skip paren
        while(input[base][c] == '.') ++c; // skip space
        const int res = expr(r, c, er, ec);
        while(input[base][c] == '.') ++c; // skip space
        ++c; // skip paren
        return res;
    } else {
        const int res = digit(base, c);
        ++c;
        return res;
    }
}

int digit(int r, int c) {
    return input[r][c] - '0';
}

bool solve() {
    input.clear();
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    input.resize(N);
    for(int i = 0; i < N; ++i) {
        cin >> input[i];
    }
    int c = 0;
    cout << expr(0, c, N, input[0].size()) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    init();
    while(solve()) ;
    return 0;
}
