#define B(x)x"B("#x")"
#define A(x)"A("#x")";x
B(char*s="#define B(x)x\"B(\"#x\")\"\n#define A(x)\"A(\"#x\")\";x\n")A(main(i,j,k){for(gets(j);~scanf("%d",&i);printf("%d\n",k))for(k=j=0;j<214;)k+=s[j++]==s[i%214];})