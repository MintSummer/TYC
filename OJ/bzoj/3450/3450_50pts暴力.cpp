#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long double LD;
    const int N=1010;
    int n;
    LD ans,p[N],dp[N][N];//dp[i][j]到第i为长为j的串的概率
    string str;

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>str;
        for(int i=1;i<=n;i++)
            switch(str[i-1])
            {
                case 'o': p[i]=1.0;break;
                case 'x': p[i]=0.0;break;
                case '?': p[i]=0.5;break;
            }
        dp[0][0]=1.0;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=i;j++)
            {
                dp[i][0]+=dp[i-1][j-1];
                dp[i][j]=dp[i-1][j-1]*p[i];
                ans+=dp[i][j]*j*j-dp[i][j]*(j-1)*(j-1);//减掉之前算的
            }
            dp[i][0]*=(1-p[i]);
        }
        cout<<fixed<<setprecision(4)<<ans<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}