#include<bits/stdc++.h>
using namespace std;
int n,G[15][15],dp[15][15][15][15];

int main()
{
    scanf("%d",&n);
    int x,y,val,i,j;
    while(scanf("%d%d%d",&x,&y,&val))
	if(x!=0&&y!=0&&val!=0) G[x][y]=val;
	else break;
    
    for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	    for(x=1;x<=n;x++)
		for(y=1;y<=n;y++)
		{
		    //i、j表示第一个人走的位置，x、y表示第二个人走的位置
		    //考虑两个人同时走
		    dp[i][j][x][y]=max(max(dp[i-1][j][x-1][y],dp[i-1][j][x][y-1]),max(dp[i][j-1][x-1][y],dp[i][j-1][x][y-1]))+G[i][j]+G[x][y];
		    if(i==x&&j==y) dp[i][j][x][y]-=G[i][j];//走到同一点上
		}
    printf("%d",dp[n][n][n][n]);
    return 0;
}
