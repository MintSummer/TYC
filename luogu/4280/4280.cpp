#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=10010,K=110,inf=0x3f3f3f3f;
    int n,k,tot,ans,pos[N],a[N],front[N][K],back[N][K],dp[N][K],f[N][K];

    void work()
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
		{
            scanf("%d",&a[i]);
			if(a[i]==-1) pos[++tot]=i;
		}
        for(int i=1;i<=n;i++)
            for(int j=1;j<=k;j++)
			    front[i][j]=front[i-1][j]+(j<a[i]);
        for(int i=n;i;i--)
            for(int j=1;j<=k;j++)
			    back[i][j]=back[i+1][j]+(~a[i]&&j>a[i]);
        for(int i=1;i<=tot;i++)
        {
			int x=pos[i];
            dp[i][1]=dp[i-1][1]+front[x][1]+back[x][1];
            f[i][1]=dp[i][1];
            for(int j=2;j<=k;j++)
            {
                dp[i][j]=f[i-1][j]+front[x][j]+back[x][j];
                f[i][j]=min(f[i][j-1],dp[i][j]);
            }
        }
		ans=inf;
        for(int i=1;i<=k;i++) ans=min(ans,dp[tot][i]);
		for(int i=1;i<=n;i++)
			if(~a[i]) ans+=back[i][a[i]];
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;    
}
