#include<bits/stdc++.h>
using namespace std;
int n,m,k,dp[110][110][15];
int G[110][3],one[110][3],two[110];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
		{
			scanf("%d",&G[i][j]);
			one[i][j]=one[i-1][j]+G[i][j];
		}
	for(int i=1;i<=n;i++) two[i]=two[i-1]+G[i][1]+G[i][2];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int p=k;p>=1;p--)
			{
				dp[i][j][p]=max(dp[i-1][j][p],dp[i][j-1][p]);
				for(int d=0;d<i;d++)
					dp[i][j][p]=max(dp[i][j][p],dp[d][j][p-1]+one[i][1]-one[d][1]);
				for(int d=0;d<j;d++)
					dp[i][j][p]=max(dp[i][j][p],dp[i][d][p-1]+one[j][2]-one[d][2]);
				int mn=min(i,j);
				for(int d=0;d<mn;d++)
					dp[i][j][p]=max(dp[i][j][p],dp[d][d][p-1]+two[mn]-two[d]);
			}
	printf("%d",dp[n][n][k]);
	return 0;
}
