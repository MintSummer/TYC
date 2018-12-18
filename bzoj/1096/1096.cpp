//tyc
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=1000010;
long long n;
long long x[MAXN],p[MAXN],c[MAXN],sp[MAXN],sum[MAXN];
long long dp[MAXN],q[MAXN];

inline double y(long long a)
{
    return dp[a]+sum[a];
}

inline double xx(long long a)
{
    return sp[a];
}

inline double g(long long a,long long b)
{
    if(sp[a]-sp[b]==0) return 0x3f3f3f3f;
    else return (y(a)-y(b))/(xx(a)-xx(b));
}

int main()
{   
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld%lld",&x[i],&p[i],&c[i]);
        sp[i]=sp[i-1]+p[i];    
        sum[i]=sum[i-1]+x[i]*p[i];
    }
    
    int h=0,t=1;
    q[0]=0;
    for(int i=1;i<=n;i++)
    {
        while( h+1<t && g(q[h],q[h+1]) < x[i] )
            h++;
        dp[i]=dp[q[h]]+x[i]*(sp[i]-sp[q[h]])-(sum[i]-sum[q[h]])+c[i];
        while( h+1<t && g(i,q[t-1]) < g(q[t-1],q[t-2]) )
            t--;
        q[t++]=i;
    }

    printf("%lld",dp[n]);
    return 0;
}
