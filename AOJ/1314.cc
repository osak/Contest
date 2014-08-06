//Name: Matrix Calculator
//Level: 3
//Category: 構文解析
//Note: ICPC Tokyo 2010 J

/**
 * 見た目やばいが、ただのLL(1)なので構文解析をがんばる。
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <cassert>

using namespace std;

struct Matrix {
    int rows, cols;
    vector<vector<int>> buf;

    explicit Matrix(int v) : rows(1), cols(1), buf(1, vector<int>(1, v)) {}
    Matrix(int r, int c) : rows(r), cols(c), buf(r, vector<int>(c, 0)) {}
    Matrix(const Matrix& m) : rows(m.rows), cols(m.cols), buf(m.buf) {}
    Matrix(Matrix&& m) : rows(m.rows), cols(m.cols), buf(std::move(m.buf)) {}

    Matrix& operator = (Matrix &&m) {
        rows = m.rows;
        cols = m.cols;
        buf = std::move(m.buf);
        return *this;
    }

    int& at(int r, int c) {
        return buf[r][c];
    }

    int at(int r, int c) const {
        return buf[r][c];
    }

    void normalize() {
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < cols; ++c) {
                if(at(r, c) < 0) {
                    at(r, c) += 32768 * ((-at(r, c) + 32767) / 32768);
                } else if(at(r, c) > 32767) {
                    at(r, c) %= 32768;
                }
            }
        }
    }

    Matrix operator +(const Matrix &other) const {
        Matrix res(rows, cols);
        for(int r = 0; r < res.rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                res.at(r, c) = at(r, c) + other.at(r, c);
            }
        }
        res.normalize();
        return res;
    }

    Matrix operator -(const Matrix &other) const {
        Matrix res(rows, cols);
        for(int r = 0; r < res.rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                res.at(r, c) = at(r, c) - other.at(r, c);
            }
        }
        res.normalize();
        return res;
    }

    Matrix operator *(const Matrix &other) const {
        Matrix res(rows, other.cols);
        for(int r = 0; r < res.rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                for(int k = 0; k < cols; ++k) {
                    res.at(r, c) += at(r, k) * other.at(k, c);
                }
            }
        }
        res.normalize();
        return res;
    }

    Matrix operator *(int a) const {
        Matrix res(rows, cols);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < cols; ++c) {
                res.at(r, c) = at(r, c) * a;
            }
        }
        res.normalize();
        return res;
    }

    Matrix transpose() const {
        Matrix res(cols, rows);
        for(int r = 0; r < res.rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                res.at(r, c) = at(c, r);
            }
        }
        return res;
    }

    Matrix concat_col(const Matrix &other) const {
        Matrix res(rows, cols + other.cols);
        for(int r = 0; r < res.rows; ++r) {
            for(int c = 0; c < cols; ++c) {
                res.at(r, c) = at(r, c);
            }
            for(int c = 0; c < other.cols; ++c) {
                res.at(r, cols + c) = other.at(r, c);
            }
        }
        return res;
    }

    Matrix concat_row(const Matrix &other) const {
        Matrix res(rows + other.rows, cols);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                res.at(r, c) = at(r, c);
            }
        }
        for(int r = 0; r < other.rows; ++r) {
            for(int c = 0; c < res.cols; ++c) {
                res.at(rows + r, c) = other.at(r, c);
            }
        }
        return res;
    }

    int as_scalar() const {
        assert(rows == 1 && cols == 1);
        return at(0, 0);
    }
};

ostream& operator <<(ostream &os, const Matrix &m) {
    for(int r = 0; r < m.rows; ++r) {
        for(int c = 0; c < m.cols; ++c) {
            if(c != 0) os << ' ';
            os << m.at(r, c);
        }
        os << endl;
    }
    return os;
}

typedef string::const_iterator Iterator;
typedef map<char, Matrix*> Env;

Matrix expr(Iterator&, Env&);

bool isprimary(char c) {
    return isdigit(c) || isupper(c) || c == '[' || c == '(' || c == '-';
}

void skip(Iterator &it, char c) {
    if(*it != c) {
        cerr << "Expected " << c << " but got " << *it << endl;
        assert(false);
    }
    ++it;
}

int inum(Iterator &it) {
    int val = 0;
    while(isdigit(*it)) {
        val *= 10;
        val += *it - '0';
        ++it;
    }
    return val;
}

Matrix var(Iterator &it, Env &env) {
    char name = *it;
    ++it;
    return *env[name];
}

Matrix row(Iterator &it, Env &env) {
    Matrix res(0, 0);
    while(isprimary(*it)) {
        if(res.cols == 0) {
            res = std::move(expr(it, env));
        } else {
            res = res.concat_col(expr(it, env));
        }
        if(*it == ' ') {
            skip(it, ' ');
        }
    }
    return res;
}

Matrix matrix(Iterator &it, Env &env) {
    Matrix res(0, 0);
    skip(it, '[');
    while(*it != ']') {
        if(res.rows == 0) {
            res = row(it, env);
        } else {
            res = res.concat_row(row(it, env));
        }
        if(*it != ']') {
            skip(it, ';');
        }
    }
    skip(it, ']');
    return res;
}

Matrix primary(Iterator &it, Env &env) {
    Matrix tmp(0, 0);
    if(isdigit(*it)) {
        tmp = Matrix(inum(it));
    } else if(isupper(*it)) {
        tmp = var(it, env);
    } else if(*it == '[') {
        tmp = matrix(it, env);
    } else if(*it == '(') {
        skip(it, '(');
        tmp = expr(it, env);
        skip(it, ')');
    }
    while(*it == '(' || *it == '\'') {
        if(*it == '(') { // Indexed
            skip(it, '(');
            Matrix r = expr(it, env);
            skip(it, ',');
            Matrix c = expr(it, env);
            skip(it, ')');
            Matrix res = Matrix(r.cols, c.cols);
            for(int ri = 0; ri < r.cols; ++ri) {
                for(int ci = 0; ci < c.cols; ++ci) {
                    res.at(ri, ci) = tmp.at(r.at(0, ri)-1, c.at(0, ci)-1);
                }
            }
            res.normalize();
            tmp = std::move(res);
        } else if(*it == '\'') { // transposed
            skip(it, '\'');
            tmp = tmp.transpose();
        }
    }
    return tmp;
}

Matrix factor(Iterator &it, Env &env) {
    if(*it == '-') {
        skip(it, '-');
        return factor(it, env) * -1;
    } else {
        return primary(it, env);
    }
}

Matrix term(Iterator &it, Env &env) {
    Matrix lhs = factor(it, env);
    while(*it == '*') {
        skip(it, '*');
        Matrix rhs = factor(it, env);
        if(lhs.rows == 1 && lhs.cols == 1) {
            lhs = rhs * lhs.as_scalar();
        } else if(rhs.rows == 1 && rhs.cols == 1) {
            lhs = lhs * rhs.as_scalar();
        } else {
            lhs = lhs * rhs;
        }
    }
    return lhs;
}

Matrix expr(Iterator &it, Env &env) {
    Matrix lhs = term(it, env);
    while(*it == '+' || *it == '-') {
        char op = *it;
        ++it;
        Matrix rhs = term(it, env);
        if(op == '+') {
            lhs = lhs + rhs;
        } else {
            lhs = lhs - rhs;
        }
    }
    return lhs;
}

Matrix assignment(Iterator &it, Env &env) {
    char name = *it;
    ++it;
    skip(it, '=');
    Matrix m = expr(it, env);
    env[name] = new Matrix(m);
    skip(it, '.');
    return m;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    cin.ignore();
    Env env;
    for(int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        //cout << line << endl;
        Iterator it = line.begin();
        Matrix m = assignment(it, env);
        cout << m;
    }
    cout << "-----" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
