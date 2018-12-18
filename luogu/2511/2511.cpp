#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=50010,p=10007;
    int n,m,len,ans,a[N],sum[N],left[N],dp[N][2];
    
    bool judge(int x)
    {
        int tot=0,cut=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]>x) return false;
            if(tot+a[i]>x) cut++,tot=0;
            tot+=a[i];
        }
        return cut<=m;
    }
    
    void work()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
        int l=0,r=sum[n],mid;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(judge(mid)) len=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%d ",len);
        m++;
        for(int i=1,j=0;i<=n&&j<=n;i++)
        {
            while(sum[i]-sum[j]>len) j++;
            left[i]=j;
        }
        for(int i=0;i<=n;i++) dp[i][0]=1;
        for(int tim=1;tim<=m;tim++)
        {
            int now=tim&1;
            for(int i=1;i<=n;i++)
                dp[i][now]=(dp[i-1][now^1]-dp[left[i]-1][now^1]+p)%p;
            dp[0][now]=0;//因为首个dp[0][0]=1,为了前缀和正确特别修改成了0
            for(int i=1;i<=n;i++) 
                dp[i][now]=(dp[i][now]+dp[i-1][now])%p;
            ans=(ans+dp[n][now]-dp[n-1][now]+p)%p;
        }
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
