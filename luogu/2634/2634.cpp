#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=20010,inf=0x3f3f3f3f;
    int n,cnt,root,sum,tot;
    int Head[MAXN],size[MAXN],f[MAXN],dis[MAXN],num[5];
    bool vis[MAXN];
    ll ans;

    struct edge
    {
		int to,next,w;
    }E[MAXN*2];

    void add(int u,int v,int w)
    {
		E[++cnt]=(edge){v,Head[u],w};	
		Head[u]=cnt;
    }

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f=(ch=='-'?1:0),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void find_root(int u,int fa)
    {
		size[u]=1;
		f[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||v==fa) continue;
			find_root(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],sum-size[u]);
		if(f[u]<f[root]) root=u;
    }

    void dfs(int u,int fa)
    {
		num[dis[u]]++;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			dis[v]=(dis[u]+E[i].w)%3;
			dfs(v,u);
		}
    }

    ll cal(int u,int c)
    {
		dis[u]=c;
		num[0]=num[1]=num[2]=0;
		dfs(u,0);
		return num[1]*num[2]*2+num[0]*num[0];//有序对*2
    }

    void solve(int u)
    {
		ans+=cal(u,0);
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			ans-=cal(v,E[i].w);
			sum=size[v];
			root=0;
			find_root(v,0);
			solve(root);
		}
    }

    ll gcd(ll x,ll y)
    {
		return y==0?x:gcd(y,x%y);
    }

    void work()
    {
		n=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read(),w=read()%3;
			add(u,v,w),add(v,u,w);
		}
		root=0;
		sum=n;
		f[0]=inf;
		find_root(1,0);
		solve(root);
		ll g=gcd(ans,n*n);
		printf("%lld/%lld",ans/g,n*n/g);
    }
}

int main()
{
    TYC::work();
    return 0;
}
