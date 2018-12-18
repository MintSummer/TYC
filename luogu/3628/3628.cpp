#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N= 1000010;
    int n,a,q[N];
    ll b,c,sum[N],dp[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline ll f(int x)
    {
        return dp[x]+a*sum[x]*sum[x]-b*sum[x];        
    }

    void work()
    {
        n=read(),a=read();
        scanf("%lld%lld",&b,&c);
        for(int i=1;i<=n;i++) 
            sum[i]=sum[i-1]+read();
        int h=0,t=0;
        for(int i=1;i<=n;i++)
        {
            while(h<t&&-2*a*sum[i]*(sum[q[h+1]]-sum[q[h]])>f(q[h])-f(q[h+1])) h++;
            int tmp=sum[i]-sum[q[h]];
            dp[i]=dp[q[h]]+a*tmp*tmp+b*tmp+c;
            while(h<t&&(sum[i]-sum[q[t]])*(f(q[t-1])-f(q[t]))>(sum[q[t]]-sum[q[t-1]])*(f(q[t])-f(i))) t--;
            q[++t]=i;
        }
        printf("%lld\n",dp[n]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
