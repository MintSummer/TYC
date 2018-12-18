#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=300010,MX=300000;
    int n,M,tot,arr[N],cnt[N],less[N];
    ll a[50],mod[50],fac[N],FacNum[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) {x=1,y=0;return;}
        exgcd(b,a%b,x,y);
        ll tmp=x;
        x=y;
        y=tmp-a/b*y;
    }

    inline ll inv(ll a,ll mod)
    {
        ll x,y;
        exgcd(a,mod,x,y);
        return (x%mod+mod)%mod;
    }

    inline ll qpow(ll x,ll tim,ll mod)
    {
        ll ans=1;
        for(;tim;tim>>=1,x=x*x%mod)
            if(tim&1) ans=ans*x%mod;
        return ans;
    }

    inline ll phi(ll x)
    {
        ll ans=x;
        for(ll p=2,lim=sqrt(x);x!=1&&p<=lim;p++)
            if(!(x%p))
            {
                while(!(x%p)) x/=p;
                ans=ans/p*(p-1);
            }
        if(x!=1) ans=ans/x*(x-1);
        return ans;
    }

    inline void GetFac(ll p,ll pk)
    {
        static int v[N],num[N];
        for(int i=1;i<=n;i++)
            if(!(i%p)) v[i]=v[i/p],num[i]=num[i/p]+1;
            else v[i]=i,num[i]=0;
        fac[0]=1;
        for(int i=1;i<=n;i++) 
        {
            fac[i]=fac[i-1]*v[i]%pk;
            FacNum[i]=FacNum[i-1]+num[i];
        }
    }

    namespace BitTree
    {
        #define lowbit(x) x&(-x)
        ll C[MX];
        
        inline void insert(int x)
        {
            for(;x<=MX;x+=lowbit(x)) C[x]++;
        }

        inline int query(int x)
        {
            int sum=0;
            for(;x>0;x-=lowbit(x)) sum+=C[x];
            return sum;
        }
    }

    ll solve(ll p,ll pk,int k)
    {
        GetFac(p,pk);
        ll Phi=phi(pk);
        memset(cnt,0,sizeof(cnt));
        ll ans=0,Same=1,t=0;
        for(int i=n;i;i--)
        {
            int x=arr[i];
            Same=Same*qpow(fac[cnt[x]],Phi-1,pk)%pk;
            t+=FacNum[cnt[x]];
            cnt[x]++;
            Same=Same*fac[cnt[x]]%pk;
            t-=FacNum[cnt[x]];
            if(t+FacNum[n-i]>=0&&t+FacNum[n-i]<k) 
                ans=(ans+fac[n-i]*less[i]%pk*qpow(Same,Phi-1,pk)%pk*qpow(p,t+FacNum[n-i],pk)%pk)%pk;
        }
        return ans;
    }

    void work()
    {
        n=read(),M=read();
        for(int i=1;i<=n;i++) 
            arr[i]=read(),cnt[arr[i]]++;
        for(int i=n;i;i--)
        {
            less[i]=BitTree::query(arr[i]-1);
            BitTree::insert(arr[i]);
        }
        ll lim=sqrt(M),tmp=M,ans=0;
        for(ll p=2;tmp!=1&&p<=lim;p++)
            if(!(tmp%p))
            {
                ll pk=1,k=0;
                while(!(tmp%p)) 
                    pk*=p,k++,tmp/=p;
                ll Mi=M/pk;
                ans=(ans+solve(p,pk,k)*inv(Mi,pk)%M*Mi%M)%M;
            }
        if(tmp!=1)
        {
            ll Mi=M/tmp;
            ans=(ans+solve(tmp,tmp,1)*inv(Mi,tmp)%M*Mi%M)%M;
        }
        printf("%lld\n",(ans+1)%M);
    }
}

int main()
{
    TYC::work();
    return 0;   
}