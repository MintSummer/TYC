#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll inf=(1LL<<60),p=998244353;
    const int N=3000;
    int n,G[N][N];
    ll v[N],r[N],x[N],dis[N][N];

    inline ll F(int a,int b)
    {
        return ((v[a]^v[b])+v[a]*v[b]%p)%p;
    }

    void work()
    {
         scanf("%d",&n);
         for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
         for(int i=1;i<=n;i++) scanf("%lld",&r[i]);
         for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
         for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                dis[i][j]=-inf;
                if(i!=j&&x[i]-r[i]<=x[j]&&x[j]<=x[i]+r[i]) G[i][j]=1;
            }
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    if(i!=j)
                    {
                        G[i][j]|=G[i][k]&G[k][j];
                        if(G[i][j]) dis[i][j]=F(i,j);
                    }
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    if(i!=j&&G[i][k]&&G[k][j])
                        dis[i][j]=max(dis[i][j],dis[i][k]+dis[k][j]);
        for(int i=1;i<=n;i++)
        {
            ll ans=0;
            for(int j=1;j<=n;j++)
                ans=max(ans,dis[j][i]);
            printf("%lld\n",ans);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}