#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,x,ans,dp[32];

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&x);
            int tmp=1;
            for(int i=0;i<=30;i++)
                if(x&(1<<i)) tmp=max(tmp,dp[i]+1);
            for(int i=0;i<=30;i++)
                if(x&(1<<i)) dp[i]=max(dp[i],tmp);
            ans=max(ans,tmp);
        }
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}