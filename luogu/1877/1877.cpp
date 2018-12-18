#include<cstdio>
#include<iostream>
using namespace std;
int n,b,m,c[60],dp[60][1010];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>b>>m;
	dp[0][b]=1;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++)
		for(int j=m;j>=0;j--)
		{
			if(j-c[i]>=0) dp[i][j]=(dp[i][j]|dp[i-1][j-c[i]]);
			if(j+c[i]<=m) dp[i][j]=(dp[i][j]|dp[i-1][j+c[i]]);
		}
	for(int i=m;i>=0;i--) 
		if(dp[n][i]) {cout<<i;return 0;}
	cout<<"-1";
	return 0;
} 
