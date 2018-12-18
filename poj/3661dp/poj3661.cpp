#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int n,m,d[10010],dp[10010][510];

int main()
{
	memset(dp,0,sizeof(dp));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	  scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)
	  {
	  	dp[i][0]=dp[i-1][0];
	  	for(int j=1;i>=j&&j<=m;j++)
	  	  {
	  	  	dp[i][0]=max(dp[i][0],dp[i-j][j]);
	  	  	dp[i][j]=dp[i-1][j-1]+d[i];
	  	  }
	  }
	printf("%d",dp[n][0]);
	return 0;
}