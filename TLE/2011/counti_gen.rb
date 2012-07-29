#!/usr/bin/ruby

print '#define B(x)x"B("#x")"'+"\x0d"+'#define A(x)"A("#x")";x'+"\x0d"+'B(char*s="#define B(x)x\"B(\"#x\")\"'+"\x0d"+'#define A(x)\"A(\"#x\")\";x'+"\x0d"+'")A(main(i,j,k){for(gets(j);~scanf("%d",&i);){for(k=j=0;j<218;)s[j++]-s[i%218]||++k;printf("%d\n",k);}})'
