//70分的神奇n2暴力（期望30qwq）
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=3010,inf=0x3f3f3f3f;
    int n,root,cnt,Head[N],money[N],leader[N],mx[N],size[N];
    ll m,tmp[N],dp[N][N];

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
        mx[u]=max_leader;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u,max(max_leader,leader[v]));
        }
    }

    void dfs(int u,int f)
    {
        size[u]=1;
        dp[u][0]=0,dp[u][1]=money[u];
        for(int k=Head[u];k;k=E[k].next)
        {
            int v=E[k].to;
            if(v==f) continue;
            dfs(v,u);
            for(int i=1;i<=size[u]+size[v];i++) tmp[i]=inf;
            for(int i=0;i<=size[u];i++)
                for(int j=0;j<=size[v];j++) 
                    tmp[i+j]=min(tmp[i+j],dp[u][i]+dp[v][j]);
            size[u]+=size[v];
            for(int i=1;i<=size[u];i++) dp[u][i]=tmp[i];
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++) 
        {
            int fa=read();
            add(fa,i);
            if(!fa) root=i;
            money[i]=read(),leader[i]=read();
        }
        dfs(root,0,leader[root]);
        memset(dp,inf,sizeof(dp));
        dfs(root,0);
        ll ans=0;
        for(int i=1;i<=n;i++) 
            for(int j=n;j;j--)
                if(dp[i][j]<=m) {ans=max(ans,(ll)j*mx[i]);break;}
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
