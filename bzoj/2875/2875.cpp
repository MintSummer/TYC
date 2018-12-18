#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef unsigned long long ull;
    ull p;

    inline ull mul(ull a,ull b)
    {
        ull ans=0;
        for(;b;b>>=1,a=(a+a)%p)
            if(b&1) ans=(ans+a)%p;
        return ans;
    }//²»±¬long longµÄ¹êËÙ³Ë 
    
    inline ull qpow(ull a,ull tim)
    {
        ull ans=1;
        for(;tim;tim>>=1,a=mul(a,a))
            if(tim&1) ans=mul(ans,a);
        return ans;
    }

    ull sum(ull a,ull c,ull n)
    {
        if(n==1) return c;
        ull ans=sum(a,c,n/2);
        ans=(ans+mul(ans,qpow(a,n/2)))%p;
        if(n&1) ans=(ans+mul(qpow(a,n-1),c))%p;
        return ans;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        ull a,c,x,n,g,ans;
        cin>>p>>a>>c>>x>>n>>g;
        ans=qpow(a,n);
        ans=mul(ans,x);
        ans=(ans+sum(a,c,n))%p;
        cout<<ans%g;
    }
}

int main()
{
    TYC::work();
    return 0;
}
