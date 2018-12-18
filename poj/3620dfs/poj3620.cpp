#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,k,ans=0,mx=0,nx,ny;
int G[110][110],vis[110][110];
int dx[5]={0,-1,0,1,0};
int dy[5]={0,0,-1,0,1};

void dfs(int x,int y)
{
	vis[x][y]=1;
	for(int i=1;i<=4;i++)
	  {
	  	nx=x+dx[i],ny=y+dy[i];
	  	if(nx>n||nx<1||ny>m||ny<1) continue;
	  	if(vis[nx][ny]==0&&G[nx][ny]==1)
	  	  {
	  	  	ans++;
	  	  	dfs(nx,ny);
	  	  }
	  }
}

int main()
{
	memset(G,0,sizeof(G));
	memset(vis,0,sizeof(vis));
	scanf("%d%d%d",&n,&m,&k);
	int xx,yy;
	for(int i=1;i<=k;i++)
	  {
	  	scanf("%d%d",&xx,&yy);
	  	G[xx][yy]=1;
	  }
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	  {
	  	if(G[i][j]==1&&vis[i][j]==0)
	  	  {
			ans=1;
			vis[i][j]=1;
			dfs(i,j);
	  	  }
	  	mx=max(ans,mx);
	  }
	printf("%d",mx);
	return 0;
}