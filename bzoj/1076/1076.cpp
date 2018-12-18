#include<bits/stdc++.h>
using namespace std;
const int MAXN=(1<<18)+10;
int n,k,a[20];
double val[20],dp[110][MAXN];

int main()
{
    scanf("%d%d",&k,&n);
    int x,tot=(1<<n)-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&val[i]);
        while(~scanf("%d",&x)&&x) a[i]+=(1<<(x-1));
    }
    for(int i=k;i;i--)
    {
        for(int s=0;s<=tot;s++)
        {
            for(int j=1;j<=n;j++)
                if((s&a[j])==a[j])
                    dp[i][s]+=max(dp[i+1][s],dp[i+1][s|(1<<(j-1))]+val[j]);
                else dp[i][s]+=dp[i+1][s];
            dp[i][s]/=n;
        }
    }
    printf("%lf",dp[1][0]);
    return 0;
}
