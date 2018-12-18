#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=500010;
    int n,s,cnt,ans=0x3f3f3f3f,start,end,Head[N],dis[N],fa[N],vis[N];

    struct edge
    {
        int to,next,w;
    }E[N<<1];

    void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||vis[v]) continue;
            fa[v]=u;
            dis[v]=dis[u]+E[i].w;
            dfs(v);
        }
    }

    void work()
    {
        scanf("%d%d",&n,&s);
        int u,v,w;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w),add(v,u,w);
        }
        dfs(1);
        for(int i=1;i<=n;i++) 
            if(dis[i]>dis[start]) start=i;
        dis[start]=0,fa[start]=0;
        dfs(start);
        for(int i=1;i<=n;i++)
            if(dis[i]>dis[end]) end=i;
        for(int i=end,j=end;i;i=fa[i])//ÅÀÖ±¾¶
        {
            while(fa[j]&&dis[i]-dis[fa[j]]<=s) j=fa[j];
            ans=min(ans,max(dis[end]-dis[i],dis[j]));
        }
        for(int i=end;i;i=fa[i]) vis[i]=1;
        for(int i=end;i;i=fa[i]) dis[i]=0,dfs(i);
        for(int i=1;i<=n;i++) ans=max(ans,dis[i]);
        printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
