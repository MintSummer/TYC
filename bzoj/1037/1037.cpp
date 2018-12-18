#include<bits/stdc++.h>
using namespace std;
const int P=12345678;
int n,m,k,ans;
int dp[155][155][25][25];
//dp[a][b][c][d]表示前a+b个人a个是男孩,b个是女孩，其中到现在男的比女的多c个，女的比男的多d个。。

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	dp[0][0][0][0]=1;
	for(int a=0;a<=n;a++)
		for(int b=0;b<=m;b++)
			for(int c=0;c<=k;c++)
				for(int d=0;d<=k;d++)
				{
					if(c+1<=k&&a+1<=n) 
						dp[a+1][b][c+1][max(0,d-1)]=(dp[a+1][b][c+1][max(0,d-1)]+dp[a][b][c][d])%P;
					if(d+1<=k&&b+1<=m)
						dp[a][b+1][max(0,c-1)][d+1]=(dp[a][b+1][max(0,c-1)][d+1]+dp[a][b][c][d])%P;
				}
	for(int i=0;i<=k;i++) 
		for(int j=0;j<=k;j++)
			ans=(ans+dp[n][m][i][j])%P;
	printf("%d",ans);
	return 0;
}
