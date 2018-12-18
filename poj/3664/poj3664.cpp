#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int n,k;
struct cow
{
	int a,b;
	int num;
}c[50010];

bool cmp2(cow p,cow q)
{
	return p.a>q.a;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	  {
	  	c[i].num=i;
	  	scanf("%d%d",&c[i].a,&c[i].b);
	  }
	sort(c+1,c+1+n,cmp2);
	int max=0;
	int ans;
	for(int i=1;i<=k;i++)
	  {
	  	if(max<c[i].b) 
	  	  {
	  	  	max=c[i].b;
	  	  	ans=c[i].num;
	  	  }
	  }
	printf("%d",ans);
	return 0;
}