#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=1110,inf=0x7fffffff;
    int st,pre[MAXN],vis[MAXN],belong[MAXN];
    ll in[MAXN];
    struct edge
    {
		int u,v;
		ll w;
    }e[20010];

    ll solve(int root,int n,int m)
    {
		ll ans=0;
		while(1)
		{
			for(int i=0;i<n;i++) in[i]=inf;
			for(int i=0;i<m;i++)
			{
				int u=e[i].u,v=e[i].v;
				if(u!=v&&e[i].w<in[v]) 
				{
					in[v]=e[i].w,pre[v]=u;
					if(u==root) st=i;
				}
			}
			for(int i=0;i<n;i++)
				if(i!=root&&in[i]==inf) return -1;
			int tot=0;
			in[root]=0;
			memset(vis,0,sizeof(vis));
			memset(belong,-1,sizeof(belong));
			int tim=0;
			for(int i=0;i<n;i++)
			{
			    tim++;
				ans+=in[i];
				int v=i;
				while(v!=root&&belong[v]==-1&&vis[v]!=tim)
					vis[v]=tim,v=pre[v];
				if(v!=root&&belong[v]==-1)
				{
					for(int u=pre[v];u!=v;u=pre[u]) belong[u]=tot;
					belong[v]=tot++;
				}
			}
			if(!tot) return ans;
			for(int i=0;i<n;i++)
				if(belong[i]==-1) belong[i]=tot++;
			for(int i=0;i<m;i++)
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
    	int n,m;
		while(~scanf("%d%d",&n,&m))
		{
		    st=0;
			ll sum=0,w;
			int u,v;
			for(int i=0;i<m;i++)
			{
				scanf("%d%d%lld",&u,&v,&w);
				e[i]=(edge){u+1,v+1,w};
				sum+=w;
			}
			sum++;
			for(int i=m;i<n+m;i++)
				e[i]=(edge){0,i-m+1,sum};
			ll ans=solve(0,n+1,n+m);
			if(ans==-1||ans>=sum*2) puts("impossible");
			else printf("%lld %d\n",ans-sum,st-m);
			puts("");//喵了个咪
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
