#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m;
int c[310][310],num[310],sum,mx=0x3f3f3f3f;

void floyd()
{
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	      if(c[i][j]>c[i][k]+c[k][j])
	        c[i][j]=c[i][k]+c[k][j],c[j][i]=c[i][j];
}

int main()
{
	memset(c,0x3f3f3f3f,sizeof(c));
	scanf("%d%d",&n,&m);
	int a;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d",&a);
	  	for(int x=1;x<=a;x++)
	  	  {
	  	  	scanf("%d",&num[x]);
	  	  	for(int j=1;j<x;j++)
				c[num[x]][num[j]]=1,c[num[j]][num[x]]=1;
	  	  }
	  }
	floyd();
    for(int i=1;i<=n;i++)
      {
      	sum=0;
      	for(int j=1;j<=n;j++)
      	  if(i!=j)
      	    {
      	      sum+=c[i][j];
      	    }
      	if(sum<mx) mx=sum;
      }
    printf("%d",mx*100/(n-1));
    return 0;
}