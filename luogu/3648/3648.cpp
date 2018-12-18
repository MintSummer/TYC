#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=100010;
    const double eps=1e-8;
    typedef long long ll;
    int n,k,q[N],cut[210][N];
    ll sum[N],dp[3][N];

    ll x(int i)
    {
        return sum[i];
    }

    ll y(int i,int d)
    {
        return dp[d][i]-sum[i]*sum[i];
    }

    double K(int a,int b,int now)
    {
        if(sum[a]==sum[b]) return -1e18;
        return (double)(y(a,now^1)-y(b,now^1))/(x(b)-x(a));
    }

    void work()
    {
        scanf("%d%d",&n,&k);
        int arr;
        for(int i=1;i<=n;i++)
            scanf("%d",&arr),sum[i]=sum[i-1]+arr;
        for(int now=1;now<=k;now++)
        {
            int h=0,t=0,d=now&1;
            for(int i=1;i<=n;i++)
            {
                while(h<t&&K(q[h],q[h+1],d)-sum[i]<=eps) h++;
                dp[d][i]=dp[d^1][q[h]]+sum[q[h]]*(sum[i]-sum[q[h]]);
                cut[now][i]=q[h];
                while(h<t&&K(q[t-1],q[t],d)-K(q[t],i,d)>=eps) t--;
                q[++t]=i;
            }
        }
        printf("%lld\n",dp[k&1][n]);
        for(int i=k,now=n;i;i--)
        {
            now=cut[i][now];
            printf("%d ",now);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
