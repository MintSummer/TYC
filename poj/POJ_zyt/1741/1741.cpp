#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,k;
struct node
{
	int to;
	int w;
	node (int a,int b):to(a),w(b){};
};
vector<node>g[10010];
int size[10010],mson[10010],root;
bool vis[10010];
void sonsize(int u,int fa)
{
	size[u]=1,mson[u]=0;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa||vis[v])continue;
		sonsize(v,u);
		size[u]+=size[v];
		mson[u]=max(mson[u],size[v]);
	}
}
void core(int r,int u,int fa)
{
	mson[u]=min(mson[u],size[r]-mson[u]);
	if(mson[u]<minn)minn=mson[u],root=u;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa||vis[v])continue;
		core(r,v,u);
	}
}
void dis(int u,int d)
{
	
}
int 
void dfs(int x)
{
	
}
int main(void)
{
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		if(!n&&!k)break;
		for(int i=0;i<n-1;i++)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			g[a].push_back(node(b,c));
			g[b].push_back(node(a,c));
		}
		
	}
	return 0;
}
