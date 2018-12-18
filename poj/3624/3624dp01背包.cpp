#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int w[4000],d[4000],dp[13000];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	  scanf("%d%d",&w[i],&d[i]);
	for(int i=1;i<=n;i++)
	  for(int j=m;j>=w[i];j--)
	    dp[j]=max(dp[j],dp[j-w[i]]+d[i]);
	printf("%d",dp[m]);
	return 0;
}
