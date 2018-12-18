#include<bits/stdc++.h>
using namespace std;
int n,m,vis[20][20],dp[20][20];

int main()
{
    int x,y;
    scanf("%d%d%d%d",&n,&m,&x,&y);
    vis[x][y]=1;
    vis[x-1][y-2]=1,vis[x-2][y-1]=1,vis[x-2][y+1]=1,vis[x-1][y+2]=1;
    vis[x+1][y-2]=1,vis[x+2][y-1]=1,vis[x+2][y+1]=1,vis[x+1][y+2]=1;

    dp[1][0]=1;
    for(int i=1;i<=n+1;i++)
	for(int j=1;j<=m+1;j++)
	{
	    if(vis[i-1][j-1]) dp[i][j]=0;
	    else dp[i][j]=dp[i-1][j]+dp[i][j-1];
	}
    printf("%d",dp[n+1][m+1]);
    return 0;
}
