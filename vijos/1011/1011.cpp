#include<bits/stdc++.h>
using namespace std;
const int MAXN=510;
int n,m,a[MAXN][MAXN],dp[MAXN][MAXN];
int dx[5]={0,1,0,-1,0},dy[5]={0,0,-1,0,1};

int dfs(int x,int y)
{
    if(dp[x][y]) return dp[x][y];
    int res=0;
    for(int i=1;i<=4;i++)
    {
	int xx=x+dx[i],yy=y+dy[i];
	if(xx<=0||xx>n||yy<=0||yy>m) continue;
	if(a[x][y]<a[xx][yy]) res=max(res,dfs(xx,yy));
    }
    return dp[x][y]=res+1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    int ans=0;
    for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) ans=max(ans, dfs(i,j));
    printf("%d",ans);
    return 0;
}
