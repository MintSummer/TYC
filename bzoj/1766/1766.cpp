#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f;
    int n,s,tot,x[110],y[110],dp[110][110][110],h[110];

    struct node
    {
        int x,y;
        bool operator < (const node &t) const
        {
            return (x<t.x)||(x==t.x&&y<t.y);
        }
    }a[110];

    int dfs(int l,int r,int height)
    {
        int &ans=dp[l][r][height];
        if(~ans) return ans;
        bool flag=1;
        for(int i=l;i<=r;i++)
            if(y[i]>h[height]) 
                {flag=0;break;}
        if(flag) return ans=0;
        int th=upper_bound(h+1,h+1+tot,s/max(1,x[r]-x[l]))-h-1;
        ans=th>height?dfs(l,r,th)+1:inf;
        for(int i=l;i<=r;i++)
            ans=min(ans,dfs(l,i,height)+dfs(i+1,r,height));
        return ans;
    }

    void work()
    {
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i].x,&a[i].y);
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++)
        {
            if(a[i].x!=a[i-1].x) x[++tot]=a[i].x;
            y[tot]=a[i].y;
        }
        memcpy(h+1,y+1,sizeof(int[tot]));
        sort(h+1,h+1+tot);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",dfs(1,tot,0));
    }
}

int main()
{
    TYC::work();
    return 0;
}
