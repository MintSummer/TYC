#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=1e6+10;
    int n,cnt,Head[MAXN],size[MAXN];
    ll ans=0;

    struct edge
    {
		int to,next,w;
    }E[MAXN*2];

    void add(int u,int v,int w)
    {
		cnt++;
		E[cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
    }

    int ABS(int x) {return x<0?-x:x;}

    void dfs(int u,int fa)
    {
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			dfs(v,u);
			ans+=(ll)E[i].w*ABS(n-size[v]-size[v]);
			size[u]+=size[v];
		}
    }

    void work()
    {
		scanf("%d",&n);
		int u,v,w;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			add(u,v,w),add(v,u,w);
		}
		dfs(1,0);
		printf("%lld",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
