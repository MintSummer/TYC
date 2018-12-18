#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e6+10;
    int n,m,a[N],num[N],s[N],t[N];
    ll sum[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    bool check(int limit)
    {
		memset(sum,0,sizeof(sum));
        for(int i=1;i<=limit;i++)
            sum[s[i]]+=num[i],sum[t[i]+1]-=num[i];
        for(int i=1;i<=n;i++)
        {
            sum[i]+=sum[i-1];
            if(sum[i]>a[i]) return false;
        }
        return true;
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=m;i++)
            num[i]=read(),s[i]=read(),t[i]=read();
        if(check(m)) {puts("0");return;}
        int l=1,r=m,mid,ans;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid)) ans=mid,l=mid+1;
            else r=mid-1;
        }
        printf("-1\n%d\n",ans+1);
    }
}

int main()
{
    TYC::work();
    return 0;
}
