#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    int n,m,s,t;
    double ans;

    ll cal(int len)
    {
        if(len<s) return 0;
        else if(len<t) return (ll)(1+len-s)*(1+len-s+1)/2;
        else return (ll)(len-t)*(t-s+1)+(ll)(t-s+1)*(t-s+1+1)/2;
    }

    double qpow(double x,int tim)
    {
        double sum=1;
        for(;tim;tim>>=1,x*=x)
            if(tim&1) sum*=x;
        return sum;
    }

    void work()
    {
        scanf("%d%d%d%d",&n,&m,&s,&t);
        for(int i=1;i<=n;i++)
        {
            double p=(double)(cal(i-1)+cal(n-i))/cal(n);
            ans+=1-qpow(p,m);
        }
        printf("%.3f",ans);
    }
}

int main()
{
    TYC::work();
    return 0;    
}