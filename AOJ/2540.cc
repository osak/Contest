//Name: Ancient Commemorative Monolith
//Level: 3
//Category: 構文解析
//Note:

/**
 * 2次元のLL(1)構文解析。
 * 問題文から条件が読み取りにくいが、
 * ・逆向きのグリフによる反転は、他のboxの中には波及しない。
 * 　・boxはboxで1文字のようにして扱う。
 * ・グリフとして読めないときに限り、そのブロックはboxとして扱う。
 * ということがわかる。
 *
 * 読んでいるseqが反転しているかは、まずは正モードで読んでいき、反転しないと読めないグリフに遭遇したら反転しているとみなす。
 * この時点で反転モードに切り替え、最初から読み直すことで対応できる。
 *
 * グリフは途中に空行を挟むことがあるので注意。
 *
 * オーダーはO((HW)^2)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    enum TermType {
        GLYPH,
        SEQUENCE,
    } type;

    Term(TermType type) : type(type) {}
    virtual ~Term() {}

    virtual void print() = 0;
};

struct Glyph : public Term {
    vector<string> pattern;
    char ch;
    int height, width;

    Glyph(const vector<string> &p, char ch) : Term(Term::GLYPH), pattern(p), ch(ch), height(p.size()), width(p[0].size()) {}
    virtual ~Glyph() {}

    bool match(const vector<string> &field, int r, int c, bool flipped) const {
        for(int dr = 0; dr < height; ++dr) {
            for(int dc = 0; dc < width; ++dc) {
                const int pc = flipped ? width-dc-1 : dc;
                if(field[r+dr][c+dc] != pattern[dr][pc]) return false;
            }
        }
        return true;
    }

    virtual void print() {
        cout << ch;
    }
};

struct Sequence : public Term {
    vector<Term*> terms;
    bool box;

    Sequence(bool box=false) : Term(Term::SEQUENCE), box(box) {}

    void reverse() {
        ::reverse(terms.begin(), terms.end());
    }

    virtual void print() {
        if(box) cout << "[";
        for(Term *t : terms) {
            t->print();
        }
        if(box) cout << "]";
    }
};

vector<Glyph*> glyphs;

bool empty_column(const vector<string> &field, const int start_r, const int start_c, const int h) {
    for(int dr = 0; dr < h; ++dr) {
        if(field[start_r + dr][start_c] != '.') return false;
    }
    return true;
}

bool empty_row(const vector<string> &field, const int start_r, const int start_c, const int w) {
    for(int dc = 0; dc < w; ++dc) {
        if(field[start_r][start_c + dc] != '.') return false;
    }
    return true;
}

Glyph* glyph(const vector<string> &field, const int start_r, const int start_c, const int w, const int h, const bool flipped=false) {
    for(Glyph *g : glyphs) {
        if(g->width == w && g->height == h) {
            if(g->match(field, start_r, start_c, flipped)) return g;
        }
    }
    return nullptr;
}

Sequence* sequence(const vector<string> &field, const int start_r, const int start_c, const int w, const int h, const bool box) {
    Sequence *seq = new Sequence(box);
    int phase = 0;

parse:
    seq->terms.clear();
    for(int c = start_c; c < start_c + w; ) {
        if(!empty_column(field, start_r, c, h)) {
            // determine bounding box
            int bw = 1;
            while(c+bw < start_c+w && !empty_column(field, start_r, c+bw, h)) ++bw;
            int bt = start_r;
            while(empty_row(field, bt, c, bw)) ++bt;
            int bh = start_r + h - bt;
            while(empty_row(field, bt+bh-1, c, bw)) --bh;
            //cout << bt << ' ' << c << ' ' << bh << ' ' << bw << endl;
            Glyph *g = nullptr;
            if(phase == 0) {
                g = glyph(field, bt, c, bw, bh);
            }
            if(!g) {
                g = glyph(field, bt, c, bw, bh, true);
                if(phase == 0 && g) {
                    phase = 1;
                    goto parse;
                }
            }
            if(g) {
                seq->terms.push_back(g);
            } else {
                Sequence *s = sequence(field, bt+1, c+1, bw-2, bh-2, true);
                seq->terms.push_back(s);
            }
            c += bw;
        } else {
            ++c;
        }
    }
    if(phase == 1) {
        seq->reverse();
    }
    return seq;
}

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;
    //cin.ignore();

    glyphs.clear();
    for(int i = 0; i < N; ++i) {
        char ch;
        int H, W;
        cin >> ch >> H >> W;
        vector<string> pat(H);
        for(int j = 0; j < H; ++j) {
            cin >> pat[j];
        }
        glyphs.push_back(new Glyph(pat, ch));
    }
    for(int _ = 0 ; _ < M; ++_) {
        int H, W;
        cin >> H >> W;
        vector<string> field(H);
        for(int i = 0; i < H; ++i) {
            cin >> field[i];
        }
        Sequence *seq = sequence(field, 0, 0, W, H, false);
        seq->print();
        cout << endl;
    }
    cout << "#" << endl;
    for(Glyph *g : glyphs) {
        delete g;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
