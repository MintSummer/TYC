#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
struct edge
{
	int to;
	int v;
};
vector<edge>g1[1010],g2[1010];
int dis[1010],ans[1010],n,m,x,maxx;
bool vis[1010];
void spfa(int s,vector<edge> (&g)[1010])
{
	queue<int>q;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		dis[i]=0x3f3f3f3f;
	dis[s]=0;
	vis[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i].to,w=g[u][i].v;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!vis[v])q.push(v),vis[v]=true;
			}
		}
	}
}
int main(void)
{
	cin>>n>>m>>x;
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		g1[a].push_back((edge){b,c});
		g2[b].push_back((edge){a,c});
	}
	spfa(x,g2);
	for(int i=1;i<=n;i++)
		ans[i]=dis[i];
	spfa(x,g1);
	for(int i=1;i<=n;i++)
	 {
	 	if(dis[i]+ans[i]>maxx)
	 		maxx=dis[i]+ans[i];
	 }
	 cout<<maxx;
	 return 0;
} 
