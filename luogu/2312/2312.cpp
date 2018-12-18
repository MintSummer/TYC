#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=1e9+7;
    int n,m,ans[1000010];
    ll a[110];

    inline ll read()
    {
        ll x=0;int f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=(x*10+ch-'0')%p,ch=getchar();
        return f?(p-x):x;
    }

    bool f(int x)
    {
        ll sum=0;
        for(int i=n;i;i--)
            sum=(sum+a[i])%p*x%p;
        return ((sum+a[0])%p)==0;
    }
    
    void work()
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++) a[i]=read();
        int tot=0;
        for(int i=1;i<=m;i++)
            if(f(i)) ans[++tot]=i;
        printf("%d\n",tot);
        for(int i=1;i<=tot;i++)
            printf("%d\n",ans[i]);
    }   
}

int main()
{
    TYC::work();
    return 0;
}
