#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=1000000007;
    const int N=110;
    int n,m,k;
    ll dp[N][N],C[N][N];

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>k>>m;
        string from,to;
        cin>>from>>to;
        int num=0;
        for(int i=0;i<n;i++)
            if(from[i]!=to[i]) num++;
        dp[0][num]=1;
        
        C[0][0]=1;
        for(int i=1;i<=n;i++)
        {
            C[i][0]=1;
            for(int j=1;j<=n;j++)
               	C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
        }

        for(int i=1;i<=k;i++)
            for(int j=0;j<=n;j++)
                if(dp[i-1][j])
                    for(int g=0;g<=min(j,m);g++)
                        if(j-g+(m-g)>=0&&j-g+(m-g)<=n)
                            dp[i][j-g+(m-g)]=(dp[i][j-g+(m-g)]+dp[i-1][j]*C[j][g]%p*C[n-j][m-g]%p)%p;
        cout<<dp[k][0]<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}
