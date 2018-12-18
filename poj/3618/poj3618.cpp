elect Code

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int t,n,x[50010];

bool cmp(int a,int b)
{
	return abs(a)<abs(b);
}

int main()
{
	scanf("%d%d",&t,&n);
	for(int i=1;i<=n;i++)
	  {
	  	scanf("%d",&x[i]);
	  }
	sort(x+1,x+1+n,cmp);
	int sum=0,ans=0;
	x[0]=0;
	for(int i=1;i<=n;i++)
	  {
	  	sum+=abs(x[i]-x[i-1]);
	  	if(sum<=t) ans++;
	  	else break;
	  }
	printf("%d",ans);
	return 0;
}