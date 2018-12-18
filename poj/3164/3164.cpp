#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

namespace TYC
{
    const int MAXN=110,inf=0x3f3f3f3f;
    int n,m,x[MAXN],y[MAXN],pre[MAXN],root,vis[MAXN],belong[MAXN];
    double in[MAXN];

    struct edge
    {
		int u,v;
		double w;
    }e[10010];

    double dis(int i,int j)
    {
		return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    }

    double solve()
    {
		double ans=0;
		while(1)
		{
			for(int i=1;i<=n;i++) in[i]=inf;
			for(int i=1;i<=m;i++) 
			{
				int u=e[i].u,v=e[i].v;
				if(u!=v&&in[v]>e[i].w) in[v]=e[i].w,pre[v]=u;
			}
			for(int i=1;i<=n;i++)
				if(i!=root&&in[i]==inf) return -1;
			in[root]=0;
			memset(vis,0,sizeof(vis));
			memset(belong,-1,sizeof(belong));
			int tot=0;
			for(int i=1;i<=n;i++)
			{
				ans+=in[i];
				int v=i;
				while(v!=root&&belong[v]==-1&&vis[v]!=i)
					vis[v]=i,v=pre[v];
				if(v!=root&&belong[v]==-1)
				{
					belong[v]=++tot;
					for(int u=pre[v];u!=v;u=pre[u]) belong[u]=tot;
				}
			}
			if(!tot) return ans;
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
		while(~scanf("%d%d",&n,&m))
		{
			int u,v;
			for(int i=1;i<=n;i++)
				scanf("%d%d",&x[i],&y[i]);
			for(int i=1;i<=m;i++)
			{
				scanf("%d%d",&u,&v);
				e[i].u=u,e[i].v=v;
				if(u!=v) e[i].w=dis(u,v);
				else e[i].w=inf;
			}
			root=1;
			double ans=solve();
			if(ans==-1) puts("poor snoopy");
			else printf("%.2f\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
