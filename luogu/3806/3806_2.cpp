//预先处理好所有的情况 1360ms luogu
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=10010,inf=0x3f3f3f3f;
    int n,q,k,cnt,root,sum,tot;
    int Head[MAXN],size[MAXN],f[MAXN],dis[MAXN],len[MAXN],ans[10000010];
    bool vis[MAXN];
    
    struct edge
    {
		int to,next,w;
    }E[MAXN*2];

    void add(int u,int v,int w)
    {
		++cnt;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void insert(int u,int v,int w)
    {
		add(u,v,w),add(v,u,w);
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
		len[++tot]=dis[u];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			dis[v]=dis[u]+E[i].w;
			dfs(v,u);
		}
    }

    void cal(int u,int c,int d)
    {
		dis[u]=c;
		tot=0;
		dfs(u,0);
		sort(len+1,len+1+tot);
		for(int i=1;i<=tot;i++)
		    for(int j=i+1;j<=tot;j++)
			ans[len[i]+len[j]]+=d;
    }

    void solve(int u)
    {
		cal(u,0,1);
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			cal(v,E[i].w,-1);
			sum=size[v];
			root=0;
			find_root(v,u);
			solve(v);
		}
    }

    void tyc()
    {
		scanf("%d%d",&n,&q);
		int u,v,w;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			insert(u,v,w);
		}
		sum=n,root=0;
		f[0]=inf;
		find_root(1,0);
		solve(root);
		while(q--)
		{
		    scanf("%d",&k);
		    if(ans[k]>0) printf("AYE\n");
		    else printf("NAY\n");
		}
    }
}

int main()
{
    TYC::tyc();
    return 0;
}
