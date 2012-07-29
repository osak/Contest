int c[10000][9];
int v[2][9];
int p;
main() {
    int T,K,Q;
    scanf("%d", &T);
    while(T--) {
        p=0;
        scanf("%d %*d %d", &K,&Q);
        while(Q--) {
            int q,i,j;
            scanf("%d", &q);
            if(q==0) {
                for(i=0;i<=K;++i)scanf("%d",c[p]+i);
                ++p;
            }
            else {
                int s=0;
                for(i=0;i<K;++i)scanf("%d",v[0]+i);
                for(i=0;i<K;++i)scanf("%d",v[1]+i);
                for(i=0;i<p;++i){
                    int f=0;
                    for(j=0;j<K;++j)if(f+=(c[i][j]<v[0][j]||c[i][j]>v[1][j]))break;
                    if(!f)s+=c[i][K];
                }
                printf("%d\n",s);
            }
        }
    }
}
