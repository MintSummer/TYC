#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=1010,inf=0x3f3f3f3f;
    int n,m,root,cnt,tim[MAXN],pre[MAXN],vis[MAXN],belong[MAXN],id[MAXN];
    double ans,money[MAXN],in[MAXN];

    struct edge
    {
		int u,v;
		double w;
    }e[20010];

    double solve()
    {
		double tmp=0;
		while(1)
		{
			for(int i=1;i<=n;i++) in[i]=inf;
			for(int i=1;i<=m;i++)
			{
				int u=e[i].u,v=e[i].v;
				if(u!=v&&e[i].w<in[v]) in[v]=e[i].w,pre[v]=u;
			}	
			int tot=0;
			in[root]=0;
			memset(vis,0,sizeof(vis));
			memset(belong,-1,sizeof(belong));
			for(int i=1;i<=n;i++)
			{
			    if(in[i]==inf) continue;
				tmp+=in[i];
				int v=i;
				while(v!=root&&belong[v]==-1&&vis[v]!=i)
					vis[v]=i,v=pre[v];
				if(v!=root&&belong[v]==-1)
				{
					belong[v]=++tot;
					for(int u=pre[v];u!=v;u=pre[u]) belong[u]=tot;
				}
			}
			if(!tot) return tmp;
			for(int i=1;i<=n;i++)
				if(belong[i]==-1) belong[i]=++tot;
			for(int i=1;i<=m;i++)
			{
				int u=e[i].u,v=e[i].v;
				e[i].u=belong[u],e[i].v=belong[v];
				if(belong[u]!=belong[v]) e[i].w-=in[v];
			}
			n=tot,root=belong[root];
		}
    }

    void work()
    {
		scanf("%d",&n);
		double w;
		for(int i=1;i<=n;i++)
		{   
			scanf("%lf%d",&money[i],&tim[i]);
			if(tim[i]) 
			{
			    id[i]=++cnt;
			    e[cnt].v=cnt,e[cnt].w=money[i];
			}
		}
		root=n=cnt+1;
		for(int i=1;i<n;i++) e[i].u=n;
		scanf("%d",&m);
		int u,v;
		while(m--)		
		{
			scanf("%d%d%lf",&u,&v,&w);
			if(!id[u]||!id[v]) continue;
			e[++cnt]=(edge){id[u],id[v],w};
			money[v]=min(money[v],w);
		}
		for(int i=1;i<=n;i++)
			if(tim[i]) ans+=(tim[i]-1)*money[i];
		m=cnt;
		printf("%.2lf\n",ans+solve());
    }
}

int main()
{
    TYC::work();
    return 0;
}
