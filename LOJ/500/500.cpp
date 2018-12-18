#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=110;
    int n,m,a[N],b[N],dp[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    bool check(int mid)
    {
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=m;j++)
                if(~dp[i-1][j])
                    for(int k=0;j+k<=m&&a[i]*k<=mid;k++)
                        dp[i][j+k]=max(dp[i][j+k],dp[i-1][j]+(mid-a[i]*k)/b[i]);
        return dp[n][m]>=m;
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++) 
            a[i]=read(),b[i]=read();
        int l=0,r=200000000,mid,ans;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
