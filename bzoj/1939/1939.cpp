#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    int n,k,a[110],dp[110][110][7];

    int dfs(int l,int r,int num)
    {
        int &ans=dp[l][r][num];
        if(~ans) return ans;
        if(l>r) return ans=0;
        if(l==r) return ans=k-num-1;
        ans=(num==k-1?dfs(l+1,r,0):dfs(l,r,num+1)+1);
        for(int i=l+1;i<=r;i++)
            if(a[l]==a[i])
                ans=min(ans,dfs(l+1,i-1,0)+dfs(i,r,min(num+1,k-1)));
        return ans;
    }

    void work()
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",dfs(1,n,0));
    }
}

int main()
{
    TYC::work();
    return 0;
}
