#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=2010;
    typedef long long ll;
    int n,black,white,cnt,Head[N],size[N];
    ll dp[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next,w;
    }E[N<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],w};
        Head[v]=cnt;
    }

    void dfs(int u,int f)
    {
        size[u]=1;
        for(int p=Head[u];p;p=E[p].next)
        {
            int v=E[p].to;
            if(v==f) continue;
			dfs(v,u);
            for(int i=min(black,size[u]);i>=0;i--)
                for(int j=min(black-i,size[v]);j>=0;j--)
				{
					ll val=(ll)j*(black-j)*E[p].w+(ll)(size[v]-j)*(white-(size[v]-j))*E[p].w;
					dp[u][i+j]=max(dp[u][i+j],dp[u][i]+dp[v][j]+val);
				}
            size[u]+=size[v];
        }
    }

    void work()
    {
        n=read(),black=read();
		white=n-black;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w);
        }
        dfs(1,0);
        printf("%lld\n",dp[1][black]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
