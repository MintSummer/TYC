#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=1000000007;
    int n,tot,num[10],a[20];
    ll dp[16][16][16][16][16][6];

    ll dfs(int a,int b,int c,int d,int e,int last)
    {
        if(~dp[a][b][c][d][e][last]) return dp[a][b][c][d][e][last];
        if(!a&&!b&&!c&&!d&&!e) return dp[a][b][c][d][e][last]=1;
        ll ans=0;
        if(a) ans+=dfs(a-1,b,c,d,e,1)*(a-(last==2))%p;
        if(b) ans+=dfs(a+1,b-1,c,d,e,2)*(b-(last==3))%p;
        if(c) ans+=dfs(a,b+1,c-1,d,e,3)*(c-(last==4))%p;
        if(d) ans+=dfs(a,b,c+1,d-1,e,4)*(d-(last==5))%p;
        if(e) ans+=dfs(a,b,c,d+1,e-1,5)*e%p;
        dp[a][b][c][d][e][last]=ans%p;
        return dp[a][b][c][d][e][last];
    }

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),num[a[i]]++;
        memset(dp,-1,sizeof(dp));
        printf("%lld\n",dfs(num[1],num[2],num[3],num[4],num[5],0));
    }
}

int main()
{
    TYC::work();
    return 0;
}