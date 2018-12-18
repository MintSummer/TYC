#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

namespace TYC
{
    typedef long long ll;
    int T,K;

    ll qpow(ll a,ll tim,ll p)
    {
        ll ans=1;
        for(;tim;tim>>=1,a=a*a%p)
            if(tim&1) ans=ans*a%p;
        return ans;
    }

    void solve1()
    {
        ll a,b,p;
        while(T--)
        {
            cin>>a>>b>>p;
            cout<<qpow(a,b,p)<<endl;
        }
    }

    ll exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) {x=1,y=0;return a;}
        ll g=exgcd(b,a%b,x,y);
        ll tmp=x;
        x=y;
        y=tmp-a/b*y;
        return g;
    }

    void solve2()
    {
        ll a,b,m;
        while(T--)
        {
            cin>>a>>m>>b;
            ll x,y,g=exgcd(a,b,x,y);
            if(m%g!=0) cout<<"Orz, I cannot find x!"<<endl;
            else
            {
                x=x*m/g;
                ll dx=b/g;
                if(x<0)
                {
                    ll tmp=ceil((double)-x/dx);
                    x+=tmp*dx;
                }
                else 
                {
                    ll tmp=floor((double)x/dx);
                    x-=tmp*dx;
                }
                cout<<x<<endl;
            }
        }
    }

    ll inv(ll a,ll p)
    {
    ll x,y,g=exgcd(a,p,x,y);
    return g==1?(x+p)%p:-1;
    }

    ll BSGS(ll a,ll b,ll p)
    {
        map<ll,int> id;
        ll m=(ll)sqrt(p+0.5),now=1;
        id[1]=0;
        for(int i=1;i<m;i++)
        {
            now=now*a%p;
            if(!id.count(now)) id[now]=i;
        }
        ll tmp=inv(qpow(a,m,p),p);
        for(int i=0;i<m;i++)
        {
            if(id.count(b)) return i*m+id[b];
            b=b*tmp%p;
        }
        return -1;
    }

    void solve3()
    {
        ll a,b,p;
        while(T--)
        {
            cin>>a>>b>>p;
            ll ans=BSGS(a,b%p,p);
            if(ans==-1) cout<<"Orz, I cannot find x!"<<endl;
            else cout<<ans<<endl;
        }
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin>>T>>K;
        if(K==1) solve1();
        else if(K==2) solve2();
        else solve3();
    }
}

int main()
{
    TYC::work();
    return 0;
}
