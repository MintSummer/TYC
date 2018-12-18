#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=50010;
    int n,m,cnt,top,scc,dfs_clock,Head[MAXN],in[MAXN],st[MAXN],dfn[MAXN],low[MAXN],belong[MAXN],ans[MAXN];

    struct edge
    {
		int to,next,w;
    }E[100010];

    void add(int u,int v,int w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void Tarjan(int u)
    {
		dfn[u]=low[u]=++dfs_clock;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v])
			{
				Tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(low[u]==dfn[u])
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

    void init()
    {
		dfs_clock=scc=top=cnt=0;
		memset(in,0,sizeof(in));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(Head,0,sizeof(Head));
		memset(belong,0,sizeof(belong));
		memset(ans,0x3f3f3f3f,sizeof(ans));
    }

    void work() 
    {
		while(~scanf("%d%d",&n,&m))
		{
			init();
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read(),w=read();
				add(u+1,v+1,w);
			}
			for(int i=1;i<=n;i++)
				if(!dfn[i]) Tarjan(i);
			for(int u=1;u<=n;u++)
				for(int i=Head[u];i;i=E[i].next)
				{
					int v=E[i].to;
					if(belong[u]==belong[v]) continue;
					ans[belong[v]]=min(ans[belong[v]],E[i].w);
				}
			long long sum=0;
			for(int i=1;i<scc;i++) sum+=ans[i];
			printf("%lld\n",sum);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
