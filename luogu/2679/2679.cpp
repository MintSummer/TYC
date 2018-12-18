#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=1000000007;
    int n,m,block;
    ll dp[2][205][205][2];
    char A[1010],B[210];

    inline void Mod(ll &x,ll y)
    {
        ll t=(ll)x+y;
        x=(int)(t>p?t-p:t);
    }

    void work()
    {
        scanf("%d%d%d",&n,&m,&block);
        scanf("%s%s",A+1,B+1);
        dp[0][0][0][0]=1;
        for(int i=1;i<=n;i++)
        {
            int now=(i&1);
            memset(dp[now],0,sizeof(dp[now]));
            dp[now][0][0][0]=1;
            for(int j=1;j<=block;j++)
                for(int k=1;k<=m;k++) 
                    dp[now][j][k][0]=(dp[now^1][j][k][0]+dp[now^1][j][k][1])%p;
            for(int k=1;k<=min(i,m);k++)
                if(A[i]==B[k])
                    for(int j=1;j<=block;j++)
                        Mod(dp[now][j][k][1],(dp[now^1][j-1][k-1][0]+dp[now^1][j][k-1][1]+dp[now^1][j-1][k-1][1])%p);
        }
        printf("%lld\n",(dp[n&1][block][m][0]+dp[n&1][block][m][1])%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}