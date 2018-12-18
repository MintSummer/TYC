#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long double LD;
    const int N=1010;
    int n,h[N],num[N];
    LD ans,fac[N];

    inline LD A(int n,int m)
    {
        return fac[n]/fac[n-m];
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n;
        fac[0]=1.0;
        for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
        for(int i=1;i<=n;i++) 
            cin>>h[i],num[h[i]]++;
        for(int i=0,s=0;i<=1000;i++)
            if(num[i])
            {
                LD tmp=0;
                for(int j=0;j<=s;j++)
                    tmp+=A(s,j)/fac[n]*fac[n-j-1]*(j+1);
                for(int j=0,lim=min(n-2,s);j<=lim;j++)
                    tmp+=A(s,j)/fac[n]*(n-s-1)*fac[n-j-2]*(n-j-1)*(j+1);
                ans+=tmp*num[i];
                s+=num[i];
            }
        cout<<fixed<<setprecision(2)<<ans<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}