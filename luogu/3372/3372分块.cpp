#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=100000+10;
    typedef long long ll;
    int n,m,block,belong[MAXN],st[MAXN],end[MAXN];
    ll a[MAXN],sum[MAXN],tag[MAXN];

    void work()
    {
        scanf("%d%d",&n,&m);
        block=sqrt(n);
        for(int i=1;i<=n;i++)
        {
            belong[i]=(i-1)/block+1;
            scanf("%lld",&a[i]);
            sum[belong[i]]+=a[i];
        }
        for(int i=1;i<=n;i++)
            st[i]=(i-1)*block+1,end[i]=min(n,i*block);
        int opt,lt,rt;
        ll w;
        while(m--)
        {
            scanf("%d%d%d",&opt,&lt,&rt);
            if(opt==1)
            {
                scanf("%lld",&w);
                if(belong[lt]==belong[rt])
                    for(int i=lt;i<=rt;i++)
                        a[i]+=w,sum[belong[lt]]+=w;
                else 
                {
                    for(int i=lt;i<=end[belong[lt]];i++)
                        a[i]+=w,sum[belong[lt]]+=w;
                    for(int i=belong[lt]+1;i<belong[rt];i++)
                        tag[i]+=w;
                    for(int i=st[belong[rt]];i<=rt;i++)
                        a[i]+=w,sum[belong[rt]]+=w;
                }
            }
            else
            {
                ll ans=0;
                if(belong[lt]==belong[rt])
                    for(int i=lt;i<=rt;i++)
                        ans+=a[i]+tag[belong[lt]];
                else
                {
                    for(int i=lt;i<=end[belong[lt]];i++)
                        ans+=a[i]+tag[belong[lt]];
                    for(int i=belong[lt]+1;i<belong[rt];i++)
                        ans+=sum[i]+tag[i]*(end[i]-st[i]+1);
                    for(int i=st[belong[rt]];i<=rt;i++)
                        ans+=a[i]+tag[belong[rt]];
                }
                printf("%lld\n",ans);
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
