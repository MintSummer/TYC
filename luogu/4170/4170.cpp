#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,dp[60][60];
    char ch[60];

    void work()
    {
		scanf("%s",ch+1);
		n=strlen(ch+1);
		memset(dp,0x3f3f3f3f,sizeof(dp));
		for(int i=1;i<=n;i++) dp[i][i]=1;
		for(int len=2;len<=n;len++)
			for(int l=1;l+len-1<=n;l++)
			{
				int r=l+len-1;
				if(ch[l]!=ch[r])
				{
					for(int k=l;k<r;k++)
					dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
				}
				else
				{
					int tmp=min(dp[l][r-1],dp[l+1][r]);
					dp[l][r]=min(dp[l][r],min(tmp,dp[l+1][r-1]+1));
				}
			}
		printf("%d",dp[1][n]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
