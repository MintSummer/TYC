#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=2e3+10;
    int n,m,a[N],dp[N],ans[N];

    void work()
    {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		dp[0]=1;
		for(int i=1;i<=n;i++)
			for(int j=m;j>=a[i];j--)
				dp[j]=(dp[j]+dp[j-a[i]])%10;
		for(int i=1;i<=n;i++)
		{
			ans[0]=1;
			for(int j=1;j<=m;j++)
			{
				if(j<a[i]) ans[j]=dp[j];
				else ans[j]=(dp[j]-ans[j-a[i]]+10)%10;
				printf("%d",ans[j]);
			}
			printf("\n");
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
