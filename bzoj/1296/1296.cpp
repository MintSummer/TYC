#include<bits/stdc++.h>
using namespace std;
int n,m,t;
int sum[55],dp[55][2510],f[55][55];

int main()
{
	scanf("%d%d%d",&n,&m,&t);
	char ch[55];
	for(int i=1;i<=n;i++)//行数
	{
		scanf("%s",ch);
		for(int j=0;j<m;j++) 
			sum[j+1]=sum[j]+(ch[j]=='1');
		for(int j=1;j<=m;j++)//在这一行上刷的次数
			for(int x=1;x<=m;x++)//刷到第几个
			{
				f[x][j]=0;
				for(int y=0;y<x;y++)//从第y+1个刷到第x个，y从0开始，保证每次至少刷一个
				{
					int black=sum[x]-sum[y],white=x-y-black;
					f[x][j]=max(f[x][j],f[y][j-1]+max(black,white));
				}
			}
		for(int j=1;j<=t;j++)//总次数
		{
			int tmp=min(j,m);
			for(int k=1;k<=tmp;k++)//枚举在这一行上刷的次数
				dp[i][j]=max(dp[i][j],dp[i-1][j-k]+f[m][k]);
		}
	}
	int ans=0;
	for(int i=1;i<=t;i++) ans=max(ans,dp[n][i]);
	printf("%d",ans);
	return 0;
}
