#include "silver.h"
#include <cstdio>
#include <cstdlib>

static int W,N,X[100000],D[100000];
static int L[100001], R[100001];
static int ans_collected;
void answer(int k, int Larg, int Rarg) {
  if( !(1 <= k && k <= N) || L[k]!=-1) {
    fprintf(stderr, "invalid library call");
    exit(1);
  }
  L[k] = Larg;
  R[k] = Rarg;
  ans_collected++;
}

int main() {
  scanf("%d%d", &W, &N);
  for(int i = 0; i < N; i++) {
    scanf("%d%d", X+i, D+i);
  }
  for(int i = 1; i <= N; i++) {
    L[i] = R[i] = -1;
  }
  ans_collected = 0;
  schedule(W, N, X, D);
  if(ans_collected < N) {
    fprintf(stderr, "too few library call");
    exit(1);
  }
  for(int i = 1; i <= N; i++) {
    printf("%d %d\n", L[i], R[i]);
  }
  return 0;
}
