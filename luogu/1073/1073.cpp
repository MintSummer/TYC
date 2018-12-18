#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=100010,M=500010,inf=0x3f3f3f3f;
    int n,m,ans,val[N],mn[N],f[N];
    vector<int> G[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void dfs(int u,int from,int Min)
    {
        Min=min(Min,val[u]);
        int flag_change=0;
        if(mn[u]>Min) mn[u]=Min,flag_change=1;
        int Max=max(f[from],val[u]-Min);
        if(f[u]<Max) f[u]=Max,flag_change=1;
        if(!flag_change) return;
        for(int i=0;i<G[u].size();i++)
            dfs(G[u][i],u,Min);
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++) val[i]=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            G[u].push_back(v);
            if(read()==2) G[v].push_back(u);
        }
        memset(mn,inf,sizeof(int[n+5]));
        dfs(1,0,inf);
        printf("%d\n",f[n]);
    }
}

int main()
{
    TYC::work();
    return 0;
}