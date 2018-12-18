#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
int n,m,b[210],ans;
bool c[210];
vector<int> g[210];
bool path(int x)
{
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(c[v])continue;
		c[v]=true;
		if(b[v]==-1||path(b[v]))
		{
			b[v]=x;
			return true;
		}
	}
	return false;
}
void hungary()
{
	memset(b,-1,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		memset(c,0,sizeof(c));
		if(path(i))ans++;
	}
}
int main(void)
{
	while(scanf("%d%d",&n,&m)==2)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			g[i].clear();
			int a,b;
			scanf("%d",&a);
			while(a--)
			{
				scanf("%d",&b);
				g[i].push_back(b);
			} 
		}
		hungary();
		printf("%d\n",ans);
	}
	return 0;
}
