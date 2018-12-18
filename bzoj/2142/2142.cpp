#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int tot;
    ll w[10],a[N],mod[N];

    ll exgcd(ll A,ll B,ll &x,ll &y)
    {
        if(!B) {x=1,y=0;return A;}
        ll gcd=exgcd(B,A%B,x,y),tmp=x;
        x=y;
        y=tmp-A/B*y;
        return gcd;
    }

    ll inv(ll n,ll p)
    {
        ll x,y;
        exgcd(n,p,x,y);
        return (x%p+p)%p;
    }

    ll qpow(ll x,ll tim,ll p)
    {
        ll ans=1;
        for(;tim;tim>>=1,x=x*x%p)
            if(tim&1) ans=ans*x%p;
        return ans;
    }

    ll fac(ll n,ll p,ll pk)
    {
        if(!n) return 1;
        ll ans=1;
        for(ll i=1;i<=pk;i++)
            if(i%p) ans=ans*i%pk;
        ans=qpow(ans,n/pk,pk);
        for(ll i=1,tmp=n%pk;i<=tmp;i++)
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
            ll x,y,b=mod[i],c=(a[i]-ans%b+b)%b;
            ll gcd=exgcd(M,b,x,y);
            b/=gcd;
            x=(x%b+b)%b;
            x=c/gcd*x%b;
            ans+=M*x;
            M*=b;
            ans=(ans+M)%M;
        }
        return ans;
    }

    ll exLucas(int n,int m,int p)
    {
		tot=0;
        ll limit=sqrt(p);
        for(ll i=2;i<=limit&&p>1;i++)
            if(!(p%i))
            {
                ll mi=1;
                while(!(p%i)) mi*=i,p/=i;
                a[++tot]=C(n,m,i,mi);
                mod[tot]=mi;
            }
        if(p>1)
            a[++tot]=C(n,m,p,p),mod[tot]=p;
        return excrt();
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        ll n,m,p,sum=0,ans=1;
        cin>>p>>n>>m;
        for(int i=1;i<=m;i++)
            cin>>w[i],sum+=w[i];
        if(sum>n) {cout<<"Impossible\n";return;}
        for(int i=1;i<=m;n-=w[i],i++)
            ans=ans*exLucas(n,w[i],p)%p;
        cout<<ans<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}
