#include<cstdio>
#include<algorithm>
#include<queue> 
#include<cstring>
#include<vector>
using namespace std;
int dis[5010],dis2[5010],n,m;
struct point
{
	int id;
	int dis;
	bool operator<(const point &b)const
	{
		return dis>b.dis;
	}
};
struct edge
{
	int to;
	int w;
};
priority_queue<point>q;
vector<edge>g[5010];
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[a].push_back((edge){b,c});
		g[b].push_back((edge){a,c});
	}
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(dis2,0x3f3f3f3f,sizeof(dis2));
	dis[1]=0;
	q.push((point){1,0});
	while(!q.empty())
	{
		int u=q.top().id,d=q.top().dis;
		q.pop();
		if(d>dis2[u])continue;
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i].to,w=g[u][i].w;
			bool flag=false;
			if(dis[v]>dis[u]+w)
				dis[v]=dis[u]+w,flag=true;
			
			if(dis[v]<dis[u]+w&&dis2[v]>dis[u]+w)
				dis2[v]=dis[u]+w,flag=true;
			
			if(dis2[v]>dis2[u]+w)
				dis2[v]=dis2[u]+w,flag=true;
				
			if(flag)q.push((point){v,dis[v]});
		}
	}
	printf("%d",dis2[n]);
	return 0;
}
