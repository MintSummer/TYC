#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=1e5,MAXN=1e5+10;
    int cnt,prime[MAXN],vis[MAXN],f[MAXN];

    inline void init()
    {
		f[1]=1;
        for(int i=2;i<=N;i++)
        {
            if(!vis[i]) prime[++cnt]=i,f[i]=f[i-1];
            for(int j=1,k;(k=i*prime[j])<=N&&j<=cnt;j++)
            {
                vis[k]=1;
                f[k]=f[i]+f[prime[j]];
                if(i%prime[j]==0) break;
            }
        }
    }

    void work()
    {
        init();
        int T,n;
        scanf("%d",&T);
        while(T--)
        {
            long long ans=0,flag=1,p,q;
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
            {
                scanf("%lld%lld",&p,&q);
                flag&=(p!=2);
                ans+=f[p]*q;
            }
            printf("%lld\n",ans+flag);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
