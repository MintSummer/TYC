#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e7;
int cnt,phi[MAXN+10],vis[MAXN+10],prime[MAXN/8+10];

int read()
{
    int x=0;int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void get_phi()
{
    phi[1]=1;
    for(int i=2;i<=MAXN;i++)
    {
        if(!vis[i]) phi[i]=i-1,prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=MAXN;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) 
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}

ll qpow(ll x,ll tim,ll p)
{
    ll ans=1;
    for(;tim;tim>>=1,x=x*x%p)
        if(tim&1) ans=ans*x%p;
    return ans;
}

ll solve(ll x)
{
    if(x==1) return 0;
    return qpow(2,solve(phi[x])+phi[x],x);
}

int main()
{
    int T=read();
    get_phi();
    while(T--)
    {
        ll p=read();
        printf("%lld\n",solve(p));
    }
    return 0;
}
