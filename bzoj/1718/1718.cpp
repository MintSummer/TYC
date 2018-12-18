#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=5010;
    int n,m,cnt,top,dfs_clock,scc,from[10000],to[10000],Head[N],dfn[N],low[N],in[N],st[N],belong[N],d[N],another[N*10];

    struct edge
    {
		int to,next;
    }E[10000*2];

    void insert(int u,int v)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v]};
		Head[v]=cnt;
    }

    void Tarjan(int u,int pre)
    {
		dfn[u]=low[u]=++dfs_clock;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(i==another[pre]) continue;
			if(!dfn[v]) 
			{
				Tarjan(v,i);
				low[u]=min(low[u],low[v]);
			}
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			scc++;
			int x;
			do
			{
				x=st[top--];
				belong[x]=scc;
				in[x]=0;
			}
			while(x!=u);
		}
    }

    void work()
    {
		scanf("%d%d",&n,&m);
		int u,v;
		for(int i=1;i<=m;i++) 
		{
			scanf("%d%d",&u,&v);
			insert(u,v);
			another[cnt]=cnt-1,another[cnt-1]=cnt;
			from[i]=u,to[i]=v;
		}
		for(int i=1;i<=n;i++) 
			if(!dfn[i]) Tarjan(i,-1);
		for(int i=1;i<=m;i++)
		{
			int u=from[i],v=to[i];
			if(belong[u]!=belong[v])
				d[belong[u]]++,d[belong[v]]++;
		}
		int ans=0;
		for(int i=1;i<=scc;i++) 
			if(d[i]==1) ans++;
		printf("%d",(ans+1)/2);
    }
}

int main()
{
    TYC::work();
    return 0;
}
