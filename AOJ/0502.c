main(n,c,t,s,k){
    for(;scanf("%d",&n)&&n;printf("%d\n",s)){
        int d[]={1,3,6,4},p=0;
        for(s=1,t=2;n--&&scanf("%s",&c);){
            c&=255;
            if(c=='E')p=++p&3;
            if(c=='W')p=--p&3;
            if(c=='N'){k=d[p];d[p]=t;d[(p+2)&3]=t+5;t=k;}
            if(c=='S'){k=d[p];d[p]=t+5;d[(p+2)&3]=t;t=k;}
            if(c=='R'){k=d[(p+1)&3];d[(p+1)&3]=

/*
5 2
1364
2 5
*/
