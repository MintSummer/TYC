#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=110,inf=0x3f3f3f3f;
    int n,m,root,pre[MAXN],vis[MAXN],belong[MAXN],in[MAXN];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int u,v,w;
    }e[10010];

    ll solve()
    {
		ll ans=0;
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
			int tot=0;
			memset(vis,0,sizeof(vis));
			memset(belong,-1,sizeof(belong));
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
		n=read(),m=read(),root=read();
		for(int i=1;i<=m;i++)
			e[i]=(edge){read(),read(),read()};
		printf("%lld",solve());
    }
}

int main()
{
    TYC::work();
    return 0;
}
