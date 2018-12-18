#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=998244353,N=1e5+10;
    int n,cnt,a[N],begin[N],end[N];
    ll ans;    
    map<ll,int> id;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    int gcd(int x,int y)
    {
        return !y?x:gcd(y,x%y);
    }

    struct node
    {
        int x,tim;
    }Gcd[N<<1];

    void work()
    {
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        begin[1]=a[1],end[n]=a[n];
        for(int i=2;i<n;i++)
        {
            begin[i]=gcd(begin[i-1],a[i]);
            ans=(ans+begin[i])%p;
        }
        for(int i=n-1;i>=2;i--)
        {
            end[i]=gcd(end[i+1],a[i]);
            ans=(ans+end[i])%p;
        }
        for(int i=1;i<=n-2;i++)
        {
            if(!id.count(begin[i]))
            {
                Gcd[++cnt]=(node){begin[i],1};
                id[begin[i]]=cnt;
            }
            else Gcd[id[begin[i]]].tim++;
            for(int j=1;j<=cnt;j++)
                ans=(ans+(ll)gcd(Gcd[j].x,end[i+2])*Gcd[j].tim%p)%p;
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
