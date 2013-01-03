#include <cstdio>
#include "animals.h"

const int MAXN = 100000;

static int N, Q, E[MAXN][2];

int main()
{
  scanf("%d", &N);
  for(int i=0; i<N-1; ++i)
    scanf("%d%d", &(E[i][0]), &(E[i][1]));

  init(N, E);

  for(int i=0; i<N-1; ++i) {
	scanf("%d", &Q);
    printf("%d", query(Q));
	if(i==N-2) puts("");
	else printf(" ");
	fflush(stdout);
  }

  return 0;
}

