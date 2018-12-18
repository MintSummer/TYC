#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int SIZE=1e6+10;
    int tot;
    ll N,M,P,a[SIZE],mod[SIZE];

    ll exgcd(ll A,ll B,ll &x,ll &y)
    {
        if(!B) {x=1,y=0;return A;}
        ll gcd=exgcd(B,A%B,x,y),tmp=x;
        x=y;
        y=tmp-A/B*y;
        return gcd;
    }

    ll inv(ll A,ll p)
    {
        ll x,y;
        exgcd(A,p,x,y);
        return (x%p+p)%p;
    }

    ll qpow(ll x,ll tim,ll p)
    {
        ll ans=1;
        for(;tim;tim>>=1,x=x*x%p) 
            if(tim&1) ans=ans*x%p;
        return ans;
    }
    
    ll mul(ll x,ll tim,ll p)
    {
        ll ans=0;
        for(;tim;tim>>=1,x=(x+x)%p)
            if(tim&1) ans=(ans+x)%p;
        return ans;
    }

    ll fac(ll n,ll p,ll pk)
    {
        if(!n) return 1;
        ll ans=1;
        for(ll i=1;i<=pk;i++)
            if(i%p) ans=ans*i%pk;
        ans=qpow(ans,n/pk,pk);
        for(ll i=1,limit=n%pk;i<=limit;i++)
            if(i%p) ans=ans*i%pk;
        return ans*fac(n/p,p,pk)%pk;
    }

    ll C(ll n,ll m,ll p,ll pk)
    {
        if(n<m) return 0;
        ll f1=fac(n,p,pk),f2=fac(m,p,pk),f3=fac(n-m,p,pk),cnt=0;
        for(ll i=n;i;i/=p) cnt+=i/p;
        for(ll i=m;i;i/=p) cnt-=i/p;
        for(ll i=n-m;i;i/=p) cnt-=i/p;
        return f1*inv(f2,pk)%pk*inv(f3,pk)%pk*qpow(p,cnt,pk)%pk;
    }

    ll excrt()
    {
        ll ans=a[1],M=mod[1];
        for(int i=2;i<=tot;i++)
        {
            ll x,y,b=mod[i],c=(a[i]-ans%mod[i]+mod[i])%mod[i];
            ll gcd=exgcd(M,b,x,y);
			b/=gcd;
            x=mul((x%b+b)%b,c/gcd,b);
            ans+=M*x;
            M*=b/gcd;
            ans=(ans%M+M)%M;
        }
		return ans;
    }

    ll exLucas(ll n,ll m,ll p)
    {
        ll limit=sqrt(p);
        for(ll i=2;p>1&&i<=limit;i++)
            if(!(p%i))
            {
                ll mi=1;
                while(!(p%i)) p/=i,mi*=i;
                a[++tot]=C(n,m,i,mi);
                mod[tot]=mi;
            }
        if(p>1) a[++tot]=C(n,m,p,p),mod[tot]=p;
        return excrt();
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>N>>M>>P;
        cout<<exLucas(N,M,P);
    }
}

int main()
{
    TYC::work();
    return 0;
}
