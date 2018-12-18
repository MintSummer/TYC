#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

namespace TYC
{
    const int MAXN=1010;
    int N,M,cnt,top,tim,tot;
    int Head[MAXN],dfn[MAXN],low[MAXN],st[MAXN],in[MAXN],belong[MAXN],du[MAXN],vis[MAXN];
    vector<int> node[MAXN];

    struct edge
    {
		int to,next;
    }E[1000010*2];

    void add(int u,int v)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		Head[u]=cnt;
    }

    void insert(int u,int v)
    {
		add(u,v),add(v,u);
    }

    void init(const int n)
    {
		cnt=tim=tot=top=0;
		memset(Head,0,sizeof(Head));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(in,0,sizeof(in));
		memset(belong,0,sizeof(belong));
		memset(du,0,sizeof(du));
		memset(vis,0,sizeof(vis));
		for (int i = 0; i <= n; i++)
			node[i].clear();
    }
    
    void Tarjan(int u,int fa)
    {
		dfn[u]=low[u]=++tim;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			if(!dfn[v])
				Tarjan(v,u),low[u]=min(low[u],low[v]);
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			tot++;
			int x;
			do
			{
				x=st[top--];
				belong[x]=tot;
				node[tot].push_back(x);
				in[x]=0;
			}
			while(x!=u);
		}
    }

    void work()
    {
		while(~scanf("%d%d",&N,&M))
		{
			init(N);
			int u,v;
			for(int i=1;i<=M;i++)
				scanf("%d%d",&u,&v),insert(u,v);
			for(int i=1;i<=N;i++)
				if(!dfn[i]) Tarjan(i,0);
			for(int u=1;u<=tot;u++)
			{
				for(int k=0;k<node[u].size();k++)
				{
					int x=node[u][k];
					for(int i=Head[x];i;i=E[i].next)
					{
						int v=belong[E[i].to];
						if(u==v||vis[v]==u) continue;
						vis[v]=u;
						du[u]++,du[v]++;
					}
				}
			}
			if(tot==1) printf("0\n");
			else 
			{
				int ans=0;
				for(int i=1;i<=tot;i++)
				{
					du[i]>>=1;
					if(du[i]==1) ans+=1;
					if(du[i]==0) ans+=2;
				}
				printf("%d\n",(ans+1)>>1);
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
