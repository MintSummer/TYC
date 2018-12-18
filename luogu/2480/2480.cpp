#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll P=999911659;
    const ll p[5]={0,2,3,4679,35617};
    ll N,G,a[7],fac[35700][5],inv[35700][5];

    inline ll qpow(ll x,ll tim,ll mod)
    {
        ll ans=1;
        for(;tim;tim>>=1,x=x*x%mod)
            if(tim&1) ans=ans*x%mod;
        return ans;
    }

    inline void init()
    {
        fac[0][1]=fac[0][2]=fac[0][3]=fac[0][4]=1;
        for(int k=1;k<=4;k++)
            for(int i=1;i<=p[k];i++)
                fac[i][k]=fac[i-1][k]*i%p[k];
        for(int k=1;k<=4;k++)
            inv[p[k]-1][k]=qpow(fac[p[k]-1][k],p[k]-2,p[k]);
        for(int k=1;k<=4;k++)
            for(int i=p[k]-2;i>=0;i--)
                inv[i][k]=inv[i+1][k]*(i+1)%p[k];
    }

    inline ll C(ll n,ll m,int k)
    {
		if(n<m) return 0;
        return fac[n][k]*inv[m][k]%p[k]*inv[n-m][k]%p[k];
    }

    inline ll Lucas(ll n,ll m,int k)
    {
		ll ans=1,mod=p[k];
		while(n&&m)
		{
			ll tmpn=n%mod,tmpm=m%mod;
			if(tmpn<tmpm) return 0;
			ans=(ans*C(tmpn,tmpm,k))%mod;
			n/=mod,m/=mod;
		}
		return ans;
    }

    void exgcd(ll A,ll B,ll &x,ll &y)
    {
        if(!B) {x=1,y=0;return;}
        exgcd(B,A%B,x,y);
        ll tmp=x;
        x=y;
        y=tmp-A/B*y;
    }

    ll crt()
    {
        ll ans=0,M=P-1;
        for(int i=1;i<=4;i++)
        {
            ll tmp=M/p[i],Inv,y;
            exgcd(tmp,p[i],Inv,y);
            Inv=(Inv%p[i]+p[i])%p[i];
            ans=(ans+a[i]*Inv%M*tmp%M)%M;
        }
		return ans;
    }

    ll solve(ll d)
    {
        for(int i=1;i<=4;i++)
            a[i]=Lucas(N,d,i);
        return crt();
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        init();
        cin>>N>>G;
        ll limit=sqrt(N),sum=0;
        for(int i=1;i<=limit;i++)
			if(!(N%i))
			{
            	if(i*i!=N) sum=(sum+solve(i)+solve(N/i))%(P-1);
				else sum=(sum+solve(i))%(P-1);
			}
		if(!(G%P)) cout<<"0";
		else cout<<qpow(G,sum,P);
    }
}

int main()
{
    TYC::work();
    return 0;
}