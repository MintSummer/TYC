//dijkstra堆优化
#include<bits/stdc++.h>
using namespace std;
const int MAXN=10010;
typedef long long ll;
int n,m,s,cnt,Head[MAXN],flag;
ll f[MAXN];

struct edge
{
	int to,next;
	ll w;
}E[500010];

struct node
{
	int num;
	ll val;
	bool operator < (const node &b) const
	{
		return val>b.val;
	}
};

void add(int u,int v,ll w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

void dijkstra()
{
	priority_queue<node> q;
	for(int i=1;i<=n;i++) f[i]=2147483647;
	f[s]=0;
	q.push((node){s,f[s]});
	int u,v;
	ll w;
	while(!q.empty())
	{
		u=q.top().num;
		q.pop();
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(f[v]>f[u]+E[i].w)
			{
				f[v]=f[u]+E[i].w;
				q.push((node){v,f[v]});
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&s);
	int u,v;
	ll w;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
	}
	dijkstra();
	for(int i=1;i<=n;i++) printf("%lld ",f[i]);
	return 0;
}
