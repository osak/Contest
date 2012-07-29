t,n,l[500],r[500],a[50],j,i;
f(){i<n&&scanf("%d",a+i++)^f();}
g(){++i<n&&(l[j%=n]=i)&&h()^h()^g();}
h(){l[(++j)%n]&&h();}
k(){++i<n&&(r[l[i]=(l[i]+n+1)%n]=i)^k();}
m(){++j<n&&(i=-1)^o()^printf("%d\n",a[(l[j]+l[n-1]+2)%n])^m();}
o(){++i<n-1&&printf("%d ",a[(l[i]+l[j]+2)%n])^o();}
main(){
	scanf("%d\n%d",&t,&n);
	f();
	qsort(a,n,4,"YXZQQQ\x8b\x00+\x02\xc3");
	i=0;g();
	i=-1;k();
	j=-1;m();
}