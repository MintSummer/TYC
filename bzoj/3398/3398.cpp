#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=100010,p=5000011;
    int n,k,dp[N],sum[N];

    void work()
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) dp[i]=1;
        for(int i=1;i<=n;i++)
        {
            if(i>k) dp[i]=(dp[i]+sum[i-k-1])%p;
            sum[i]=(sum[i-1]+dp[i])%p;
        }
        printf("%d\n",sum[n]+1);
    }
}

int main()
{
    TYC::work();
    return 0;
}
