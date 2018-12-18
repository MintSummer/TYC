#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,c[2510],sum[2510],dp[2510][2510];

inline int s(int a,int b)
{
	return sum[a]-sum[b];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
	  scanf("%d",&c[i]),sum[i]=sum[i-1]+c[i];
	dp[0][0]=0;
	dp[1][0]=dp[1][1]=m+c[1];
	for(int i=2;i<=n;i++)
	  {
	  	dp[i][1]=dp[i-1][0]+m+c[1]+m;
	  	dp[i][0]=dp[i][1];
	  	for(int j=2;j<=i;j++)
	  	  {
	  	  	dp[i][j]=dp[i-j+1][1]+s(j,1);
	  	  	dp[i][0]=min(dp[i][0],dp[i][j]);
	  	  }
	  }
	printf("%d",dp[n][0]);
	return 0;
}
