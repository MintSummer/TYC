#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=510;
int n,k;
int G[MAXN][MAXN],vis[MAXN],fa[MAXN];

bool Path(int x)
{
	for(int i=1;i<=n;i++)
	  if(G[x][i]&&!vis[i])
	    {
	      vis[i]=1;
	      if(fa[i]==-1||Path(fa[i]))
	        {
	        	fa[i]=x;
	        	return true;
	        }
	    }
	return false;
}

int Hungary()
{
	int ans=0;
	memset(fa,-1,sizeof(fa));
	for(int i=1;i<=n;i++)
	  {
	  	memset(vis,0,sizeof(vis));
	  	if(Path(i)) ans++;
	  }
	return ans;
}

int main()
{
	int x,y;
	while(scanf("%d%d",&n,&k)!=EOF)
	  {
	  	memset(G,0,sizeof(G));
	  	for(int i=1;i<=k;i++)
	  	  {
	  	  	scanf("%d%d",&x,&y);
	  	    G[x][y]=1;
	  	  }
	  	printf("%d\n",Hungary());
	  }
	return 0;
}
