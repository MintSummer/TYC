#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pa;
const int MAXN=5010;
int n,m,s,t,cnt=0;
int Head[MAXN],dis[MAXN],vis[MAXN],pre[MAXN];
queue<int> q;
pa ans;

struct edge
{
	int from,to,next,w,c;
}E[50010*2];

void add(int u,int v,int w,int c)
{
	E[cnt]=(edge){u,v,Head[u],w,c};
	Head[u]=cnt;
	cnt++;
}

bool spfa()
{
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	vis[s]=1,dis[s]=0;
	q.push(s);
	int u,v;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=Head[u];i!=-1;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w&&dis[v]>dis[u]+E[i].c)
			{
				dis[v]=dis[u]+E[i].c;
				pre[v]=i;
				if(!vis[v]) vis[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=0x3f3f3f3f;
}

void getans()
{
	ans=make_pair(0,0);
	while(spfa())
	{
		int i=pre[t],mn=0x3f3f3f3f;
		while(i!=-1)
		{
			mn=min(mn,E[i].w);
			i=pre[E[i].from];
		}
		i=pre[t];
		while(i!=-1)
		{
			E[i].w-=mn,E[i^1].w+=mn;
			i=pre[E[i].from];
		}
		ans.first+=mn;
		ans.second+=mn*dis[t];
	}
}

int main()
{
	memset(Head,-1,sizeof(Head));
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int u,v,w,c;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&u,&v,&w,&c);
		add(u,v,w,c),add(v,u,0,-c);
	}
	getans();
	printf("%d %d",ans.first,ans.second);
	return 0;
}
