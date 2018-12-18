#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int inf=0x3f3f3f3f,N=(1<<12)+10;
    int n,m,G[15][15],bin[15];
    ll dis[N][15],f[N][N],dp[15][N];

    void work()
    {
        scanf("%d%d",&n,&m);
        memset(G,inf,sizeof(G));
        bin[1]=1;
        for(int i=2;i<=n;i++) bin[i]=bin[i-1]<<1;
        int u,v,w;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            G[u][v]=G[v][u]=min(G[u][v],w);
        }
        memset(dis,inf,sizeof(dis));
        for(int i=1;i<(1<<n);i++)
            for(int u=1;u<=n;u++)
                if(i&bin[u])
                    for(int v=-1;v<=n;v++)
                        if(!(i&bin[v])&&G[u][v]!=inf)
                            dis[i][v]=min(dis[i][v],(ll)G[u][v]);
        for(int i=1;i<(1<<n);i++)
            for(int j=i&(i-1);j;j=(j-1)&i)
                for(int k=1;k<=n;k++)
                    if((i^j)&bin[k])
                        f[j][i]=min((ll)inf,f[j][i]+dis[j][k]);
        memset(dp,inf,sizeof(dp));
        for(int i=1;i<=n;i++) 
            dp[1][bin[i]]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<(1<<n);j++)
                for(int k=j&(j-1);k;k=(k-1)&j)
                    dp[i][j]=min(dp[i][j],dp[i-1][k]+(ll)f[k][j]*(i-1));
        ll ans=(1LL<<60);
        for(int i=1;i<=n;i++) 
            ans=min(ans,dp[i][(1<<n)-1]);
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
