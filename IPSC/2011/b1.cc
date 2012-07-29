#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

#define MAXS 607

int r, c, sr, sc, size, max_size;
char A[MAXS][MAXS];
int D[MAXS][MAXS];
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};
queue<pair<int, int> > Q;

int BFS() {
	Q.push(pair<int, int>(sr, sc));
	size = max_size = 1;
	D[sr][sc] = 0;

	while (!Q.empty()) {
		int ar = Q.front().first;
		int ac = Q.front().second;
		Q.pop();
		--size;
		for (int i = 0; i < 4; ++i) {
			int nr = ar + dr[i], nc = ac + dc[i];
			if (nr < 0 || r <= nr || nc < 0 || c <= nc)
				continue;
			if (A[nr][nc] == 'T')
				return D[ar][ac] + 1;
			if (A[nr][nc] == '.' && D[nr][nc] == -1) {
				D[nr][nc] = D[ar][ac] + 1;
				Q.push(pair<int, int>(nr, nc));
				++size;
				max_size = max(max_size, size);
			}
		}
	}

	return -1;
}

int main() {
	scanf("%d %d ", &r, &c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			scanf("%c ", &A[i][j]);

	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j) {
			D[i][j] = -1;
			if (A[i][j] == 'S') {
				sr = i;
				sc = j;
			}
		}

	printf("%d\n", BFS());
	printf("%d\n", max_size);
}
