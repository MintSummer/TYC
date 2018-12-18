#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=10000000;
    bool vis[N+5];
    int cnt,T,p,n,m,prime[800010],pos[N+5],fac[N+5],inv[N+5],Pi[N+5],Inv[N+5];

    inline void init()
    {
        for(int i=2;i<=N;i++)
        {
            if(!vis[i]) prime[++cnt]=i;
            for(int j=1;j<=cnt&&i*prime[j]<=N;j++)
            {
                vis[i*prime[j]]=1;
                if(!(i%prime[j])) break;
            }
        }
        fac[0]=inv[1]=Pi[0]=Inv[0]=1LL;
        for(int i=2;i<=N;i++) inv[i]=1LL*inv[p%i]*(p-p/i)%p;
        for(int i=2;i<=N;i++) pos[i]=pos[i-1]+(!vis[i]);
        for(int i=1;i<=cnt;i++) Pi[i]=1LL*Pi[i-1]*(prime[i]-1)%p;
        for(int i=1;i<=N;i++) 
            if(i!=p) fac[i]=1LL*fac[i-1]*i%p;
            else fac[i]=fac[i-1];
        for(int i=1;i<=cnt;i++) 
            if(prime[i]!=p) Inv[i]=1LL*Inv[i-1]*inv[prime[i]]%p;
            else Inv[i]=Inv[i-1];
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>T>>p;
        init();
        while(T--)
        {
            cin>>n>>m;
            if(n>=p&&m<p) cout<<"0\n";
            else cout<<1LL*fac[n]*Pi[pos[m]]%p*Inv[pos[m]]%p<<"\n";
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
