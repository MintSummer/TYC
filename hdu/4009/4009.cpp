#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=2010,inf=0x3f3f3f3f;
    int n,m,root,a,b,c,x[MAXN],y[MAXN],z[MAXN],in[MAXN],pre[MAXN],vis[MAXN],belong[MAXN];

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
    }e[MAXN*MAXN];

    inline int dis(int i,int j)
    {
		int d=abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j]);
		if(z[i]>=z[j]) return d*b;
		else return d*b+c;
    }

    ll solve()
    {
		ll ans=0;
		while(1)
		{
			for(int i=1;i<=n;i++) in[i]=inf;
			for(int i=1;i<=m;i++)
			{
				int u=e[i].u,v=e[i].v;
				if(u!=v&&e[i].w<in[v]) in[v]=e[i].w,pre[v]=u;
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
				if(e[i].u!=e[i].v) e[i].w-=in[v];
			}
			n=tot,root=belong[root];
		}
    }

    void work()
    {
	while(1)
	{
	    n=read(),a=read(),b=read(),c=read();
	    if(!n&&!a&&!b&&!c) return;
	    for(int i=1;i<=n;i++)
			x[i]=read(),y[i]=read(),z[i]=read();
	    root=n+1;
	    m=0;
	    for(int i=1;i<=n;i++)
	    {
			e[++m].u=root,e[m].v=i;
			e[m].w=z[i]*a;
			int num=read();
			while(num--)
			{
				int j=read();
				e[++m]=(edge){i,j,dis(i,j)};
			}
	    }
	    n++;
	    printf("%lld\n",solve());
	}
    }
}

int main()
{
    TYC::work();
    return 0;
}
