#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=1010;
int n,m,ans=0;
int G[MAXN][MAXN],vis[MAXN],fa[MAXN];

bool Path(int x)
{
	for(int i=1;i<=m;i++)
	  {
	  	if(G[x][i]&&!vis[i])
	  	  {
	  	  	vis[i]=1;
	  	  	if(fa[i]==-1||Path(fa[i]))
	  	  	  {
	  	  	  	fa[i]=x;
	  	  	  	return true;
	  	  	  }
	  	  }
	  }
	return false;
}

void Hungary()
{
	memset(fa,-1,sizeof(fa));
	for(int i=1;i<=n;i++)
	  {
	  	memset(vis,0,sizeof(vis));
	  	if(Path(i)) ans++;
	  }
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	  {
	  	memset(G,0,sizeof(G));
		int s,t;
		ans=0;
    	for(int i=1;i<=n;i++)
	      {
	  	    scanf("%d",&s);
	  	    while(s--)
	  	      {
	  	  	    scanf("%d",&t);
	  	  	    G[i][t]=1;
	  	      }
	      }
	    Hungary();
	  }
	return 0;
}