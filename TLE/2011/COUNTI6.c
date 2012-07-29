#define B(x,y)x"B("#x","#y")"y
B(char*s="#define B(x,y)x\"B(\"#x\",\"#y\")\"y\n",;main(i,j,k){for(gets(j);~scanf("%d",&i);printf("%d\n",k))for(k=j=0;s[j];)k+=s[j++]==s[i%177];})