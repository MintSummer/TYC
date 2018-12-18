#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=2e5+10,M=1e6;
    int n,cnt,Head[N];
    ll dp[N],sum[N],magic[N],physics[N];
    vector<int> to[N];
    bool vis[N];
    queue<int> q;

    struct edge
    {
        int to,next;
    }E[M<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void spfa()
    {
        while(!q.empty())
        {
            int u=q.front();q.pop();
			vis[u]=1;
            if(sum[u]>=dp[u]) continue;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(vis[v]) vis[v]=0,q.push(v);
                sum[v]-=dp[u];
                sum[v]+=sum[u];
            }
            dp[u]=sum[u];
        }
    }

    void work()
    {
        scanf("%d",&n);
        int num,x;
        for(int i=1;i<=n;i++)
        {
            q.push(i);
            scanf("%lld%lld%d",&physics[i],&magic[i],&num);
            while(num--)
            {
                scanf("%d",&x);
                add(x,i);
                to[i].push_back(x);
            }
        }
        for(int now=1;now<=n;now++)
        {
            dp[now]=magic[now];
            sum[now]=physics[now];
            for(int i=0;i<to[now].size();i++)
                sum[now]+=magic[to[now][i]];
        }
        spfa();
        printf("%lld\n",dp[1]);
    }
}

int main()
{
	freopen("a.in","r",stdin);
    TYC::work();
    return 0;
}
