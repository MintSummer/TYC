#include<bits/stdc++.h>
using namespace std;

namespace ZPS
{
    const int N=100010;
    int cnt,size[N],sum[N],val[N],ls[N],rs[N],dis[N];

    inline int newnode(int w)
    {
        ++cnt;
        size[cnt]=dis[cnt]=1;
        sum[cnt]=val[cnt]=w;
        ls[cnt]=rs[cnt]=0;
        return cnt;
    }

    inline void update(int root)
    {
        size[root]=size[ls[root]]+size[rs[root]]+1;
        sum[root]=sum[ls[root]]+sum[rs[root]]+val[root];
    }

    int merge(int x,int y)
    {
        if(!x||!y) return x+y;
        if(val[x]<val[y]) swap(x,y);
        rs[x]=merge(rs[x],y);
        if(dis[rs[x]]>dis[ls[x]]) swap(ls[x],rs[x]);
        dis[x]=dis[rs[x]]+1;
        update(x);
        return x;
    }

    inline int del(int root)
    {
        return merge(ls[root],rs[root]);
    }
}

namespace TYC
{
    typedef long long ll;
    const int N=100010,inf=0x3f3f3f3f;
    int n,rt,cnt,Head[N],money[N],leader[N],root[N];
    ll m,ans;

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
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v]};
        Head[v]=cnt;
    }
    
    void dfs(int u,int f,int max_leader)
    {
        root[u]=ZPS::newnode(money[u]);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u,max(max_leader,leader[v]));
            root[u]=ZPS::merge(root[u],root[v]);
            while(ZPS::size[root[u]]&&ZPS::sum[root[u]]>m) 
                root[u]=ZPS::del(root[u]);
        }
        ans=max(ans,(ll)ZPS::size[root[u]]*max_leader);
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++) 
        {
            int fa=read();
            add(fa,i);
            if(!fa) rt=i;
            money[i]=read(),leader[i]=read();
        }
        dfs(rt,0,leader[rt]);
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
