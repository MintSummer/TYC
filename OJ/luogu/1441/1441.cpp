#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    int n,m,sum,ans,a[30],dp[30000],del[30];

    inline void getans()
    {
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        int mx=0,last=0;
        for(int i=1;i<=n;i++) 
            if(!del[i])
            {
                for(int j=sum;j>=a[i];j--)
                    dp[j]|=dp[j-a[i]];
                last=i;
            }
        for(int i=1;i<=sum;i++)
            if(dp[i]) mx++;
        ans=max(ans,mx); 
    }

    void dfs(int now,int res)
    {
        if(!res) {getans();return;}
        if(now>n) return;
        dfs(now+1,res);
        del[now]=1;
        dfs(now+1,res-1);
        del[now]=0;
    }

    void work()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),sum+=a[i];
        dfs(1,m);
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}