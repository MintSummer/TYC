#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10; 
    int n,cnt,Head[N];
    ll bin[35],dis[N];
    
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
        ll w;
    }E[N<<1];

    inline void add(int u,int v,ll w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    namespace Trie
    {
        const int M=N*70;
        int cnt,son[M][2];

        inline void insert(ll x)
        {
            int now=0;
            for(int i=1;i<=32;i++)
            {
                int t=((x&bin[i])!=0);
                if(!son[now][t]) son[now][t]=++cnt;
                now=son[now][t];
            }
        }

        inline ll search(ll x)
        {
            int now=0;
            ll ans=0;
            for(int i=1;i<=32;i++)
            {
                int t=((x&bin[i])!=0);
                if(son[now][t^1]) 
                    now=son[now][t^1],ans+=bin[i];
                else now=son[now][t];
            }
			return ans;
        }
    }

    void dfs(int u,int f)
    {
        Trie::insert(dis[u]);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dis[v]=dis[u]^E[i].w;
            dfs(v,u);
        }
    }

    void work()
    {
        for(int i=0;i<=32;i++) bin[i]=(1LL<<(32-i));
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w),add(v,u,w);
        }
        dfs(1,0);
        ll ans=0;
        for(int i=1;i<=n;i++)
             ans=max(ans,Trie::search(dis[i]));
		printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
