#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=5010;
    int R,B;
    double dp[2][N];

    void work()
    {
        scanf("%d%d",&R,&B);
        for(int i=0;i<=R;i++)
            for(int j=0;j<=B;j++)
            {
                int now=(i&1);
                dp[now][j]=0;
                if(i) dp[now][j]+=(double)(dp[now^1][j]+1)*i/(i+j);
                if(j) dp[now][j]+=(double)(dp[now][j-1]-1)*j/(i+j);
                dp[now][j]=max(0.0,dp[now][j]);
            }
        printf("%.6f",floor(dp[R&1][B]*1e6)/1e6);
    }
}

int main()
{
    TYC::work();
    return 0;
}