//70pts枚举树形
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int inf=0x3f3f3f3f;
    int n,m,G[15][15],dep[15];
    ll ans=(1LL<<60);

    void dfs(int num,ll sum)
    {
        if(sum>=ans) return;
		if(num==n) {ans=sum;return;}
        for(int i=1;i<=n;i++) 
            if(~dep[i])
                for(int j=1;j<=n;j++) 
                    if(G[i][j]!=inf&&dep[j]==-1)
                    {
                        dep[j]=dep[i]+1;
                        dfs(num+1,sum+G[i][j]*dep[j]);
                        dep[j]=-1;
                    }
    }

    void work()
    {
        scanf("%d%d",&n,&m);
        memset(G,inf,sizeof(G));
        int u,v,w;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            G[u][v]=G[v][u]=min(G[u][v],w);
        }
		memset(dep,-1,sizeof(dep));
        for(int i=1;i<=n;i++)
        {
            dep[i]=0;
            dfs(1,0);
            dep[i]=-1;
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
