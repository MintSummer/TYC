#include<bits/stdc++.h>
using  namespace std;

namespace TYC
{
    const int N=60,NUM=100010,inf=0x3f3f3f3f;
    int n,m,cnt,a[N],dp[NUM],prime[NUM];
    bool vis[NUM];

    inline void get_prime()
    {
        for(int i=2;i<=m;i++)
        {
            if(!vis[i]) prime[++cnt]=i;
            for(int j=1;j<=cnt&&i*prime[j]<=m;j++)
            {
                vis[i*prime[j]]=1;
                if(i%prime[j]==0) break;
            }
        }
    }

    int calc(int x,int y)
    {
        int sum=0;
        for(int i=1;i<=n;i++)
            sum+=a[i]%y/x;
        return sum;
    }

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),m=max(m,a[i]); 
        get_prime();
        memset(dp,inf,sizeof(int[m+10]));
        int ans=inf;
        dp[1]=0;
        for(int i=1;i<=m;i++)
        {
            ans=min(ans,dp[i]+calc(i,inf));
            for(int j=1,k;j<=cnt&&(k=i*prime[j])<=m;j++)
                dp[k]=min(dp[k],dp[i]+calc(i,k));
        }
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
