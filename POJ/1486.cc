//Name: Sorting Slides
//Level: 4
//Category: グラフ,Graph,二部マッチング,探索
//Note:

/*
 * 各スライドsについて，そのスライドの内部にある番号のそれぞれについてペアを仮確定させ，
 * 残りの頂点を完全二部マッチングできるかどうか判定する．
 * このとき，sに対して上記の条件を満たすスライド番号が1つしか存在しない場合，このペアは確定される．
 * (もしそうでないと，全体で完全マッチングが形成できないため)．
 *
 * オーダーは O(N^3 + N^2 E)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

typedef vector<int> GraphRow;
typedef vector<GraphRow> Graph;

struct Slide {
    int left, right, top, bottom;
};

bool between(int a, int x, int b) {
    return a < x && x < b;
}

Graph graph;
int to[52];
bool visited[52];

bool dfs(int pos, int page) {
    if(pos == -1) return true;
    FOREACH(it, graph[pos]) {
        if(*it != page && !visited[*it]) {
            visited[*it] = true;
            if(dfs(to[*it], page)) {
                to[pos] = *it;
                to[*it] = pos;
                return true;
            }
        }
    }
    return false;
}

int bipartite_matching(int L, int slide, int page) {
    const int N = graph.size();
    fill_n(to, N, -1);
    to[slide] = page;
    to[page] = slide;
    int cnt = 0;
    TIMES(i, L) {
        if(i != slide) {
            fill_n(visited, N, false);
            if(dfs(i, page)) ++cnt;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int CASE = 1; ; ++CASE) {
        int N;
        cin >> N;
        if(!N) break;

        graph.clear();
        graph.resize(N*2);
        vector<Slide> slides;
        TIMES(_, N) {
            Slide slide;
            cin >> slide.left >> slide.right >> slide.top >> slide.bottom;
            slides.push_back(slide);
        }
        TIMES(page, N) {
            int x, y;
            cin >> x >> y;
            TIMES(slideidx, N) {
                const Slide &slide = slides[slideidx];
                if(between(slide.left, x, slide.right) &&
                   between(slide.top, y, slide.bottom))
                {
                    graph[slideidx].push_back(N+page);
                }
            }
        }

        // Try all pair as fix matching
        vector<pair<char,int> > ans;
        TIMES(slide, N) {
            int only_match = -1;
            //cout << graph[slide].size() << endl;
            FOREACH(it, graph[slide]) {
                const int page = *it;
                int cnt = bipartite_matching(N, slide, page);
                //cout << slide << ' ' << page << ' ' << cnt << endl;
                if(cnt == N-1) {
                    if(only_match == -1) {
                        only_match = page;
                    } else {
                        goto nextslide;
                    }
                }
            }
            if(only_match != -1) ans.push_back(make_pair('A'+slide, only_match));
nextslide:
            ;
        }
        cout << "Heap " << CASE << endl;
        if(ans.size() == 0) {
            cout << "none" << endl;
        } else {
            FOREACH(it, ans) {
                if(it != ans.begin()) cout << ' ';
                cout << "(" << it->first << "," << it->second-N+1 << ")";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
