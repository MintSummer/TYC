#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
char st[1000];
int a[30],vis[30];

int main()
{
	for(int i=0;i<=30;i++)
	  {
	  	a[i]=0;
	  	vis[i]=0;
	  }
	int p,len=0;
	int cnt=0;
	while(scanf("%c",&st[cnt])==1)
	  {
	  	if(st[cnt]>='A'&&st[cnt]<='Z')
	  	  {
	  	  	p=st[cnt]-'A';
	  	    a[p]++;
		    cnt++;
	  	  }
	  }
	for(int i=0;i<=25;i++)
	  {
	  	len=max(len,a[i]);
	  }
	for(int i=0;i<len;i++)
	  {
	  	for(int j=0;j<=25;j++)
	  	  {
	  	  	if(a[j]==len-i) 
	  	  	  {
	  	  	  	vis[j]=1;
	  	  	  }
	  	  	if(vis[j]==1) printf("*");
	  	  	else printf(" ");
	  	  	printf(" ");
	  	  }
	  	printf("\n");
	  }
	for(int i=0;i<=25;i++)
	  {
	  	printf("%c ",i+'A');
	  }
	return 0;
}