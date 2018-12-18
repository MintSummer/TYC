#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1e5+10;
    typedef long long ll;
    #define lowbit(x) x&(-x)
    int n,m,c[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct node
    {
        int id,val;
        bool operator < (const node &t) const
        {
            return val>t.val;
        }
    }a[N];

    void add(int x,int val)
    {
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }

    int query(int x)
    {
        int sum=0;
        for(;x;x-=lowbit(x)) sum+=c[x];
        return sum;
    }

    void work()
    {
        n=read(),m=read();
        for(int i=n;i;i--) 
            a[i]=(node){i,read()};
        for(int i=1;i<=m;i++) 
            a[++n]=(node){n,read()};
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++) add(i,1);
        ll ans=0;
        int p1=n-m,p2=p1+1;
        for(int i=1;i<=n;i++)
        {
            int now=a[i].id;
            if(now>=p2) 
            {
                ans+=query(now-1)-query(p2-1);
                p2=now,p1=p2-1;
            }
            else 
            {
                ans+=query(p1)-query(now);
                p1=now,p2=p1+1;
            }
            add(now,-1); 
        }
        printf("%lld\n",ans);
    }
} 

int main()
{
    TYC::work();
    return 0;
}
