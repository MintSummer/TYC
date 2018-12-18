#include<bits/stdc++.h>
using namespace std;

namespace TYC
{   
    typedef long long ll;
    const int N=200010;
    int n,k,p,last[110],num[110],sum[110];
    ll ans;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void work()
    {
        n=read(),k=read(),p=read();
        int mn=0;
        for(int i=1;i<=n;i++)
        {
            int col=read(),cost=read();
            if(cost<=p) mn=i;
            if(mn>=last[col]) sum[col]=num[col];
            last[col]=i;
            ans+=sum[col];
            num[col]++;
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
