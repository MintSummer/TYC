#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=3010,inf=0x3f3f3f3f;
    int n,k,cnt,Head[N],size[N],dp[N][N][3];   

    struct edge
    {
        int to,next,w;
    }E[N<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u,int f)
    {
		size[u]=1;
        dp[u][1][0]=dp[u][1][1]=0;
        for(int p=Head[u];p;p=E[p].next)
        {
            int v=E[p].to;
            if(v==f) continue;
            dfs(v,u);
            for(int i=min(k,size[u]);i;i--)
                for(int j=min(k-i,size[v]);j;j--)
                {
                    dp[u][i+j][0]=min(dp[u][i+j][0],dp[u][i][0]+dp[v][j][0]+E[p].w);
                    dp[u][i+j][1]=min(dp[u][i+j][1],dp[u][i][1]+(dp[v][j][0]+E[p].w)*2);
                    dp[u][i+j][1]=min(dp[u][i+j][1],dp[u][i][0]*2+dp[v][j][1]+E[p].w);
                    dp[u][i+j][2]=min(dp[u][i+j][2],dp[u][i][2]+(dp[v][j][0]+E[p].w)*2);
                    dp[u][i+j][2]=min(dp[u][i+j][2],(dp[u][i][0]+E[p].w)*2+dp[v][j][2]);
                    dp[u][i+j][2]=min(dp[u][i+j][2],dp[u][i][1]+dp[v][j][1]+E[p].w);
                }
            size[u]+=size[v];
        }
    }

    void work()
    {
		scanf("%d%d",&n,&k);
		int u,v,w;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w),add(v,u,w);
        }
        memset(dp,inf,sizeof(dp));
        dfs(1,0);
        int ans=inf;
        for(int i=1;i<=n;i++) 
            ans=min(ans,min(dp[i][k][1],dp[i][k][2]));
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}