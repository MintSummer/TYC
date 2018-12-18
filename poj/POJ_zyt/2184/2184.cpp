#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int M=110*1010*2,inf=-0x3f3f3f3f;
int s[110],f[110],n,dp[M+20],ans;
int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d",s+i,f+i);
	for(int i=0;i<=M;i++)dp[i]=inf;
	dp[M/2]=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]<0&&f[i]<0)continue;
		if(s[i]<0)
		{
			for(int j=0;j<=M+s[i];j++) 
				if(dp[j-s[i]]>inf)
					dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
		}
		else
			for(int j=M;j>=s[i];j--)
				if(dp[j-s[i]]>inf)
					dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
	}
	ans=inf;
	for(int i=M/2;i<=M;i++)
		if(dp[i]>=0)
			ans=max(ans,i+dp[i]-M/2);
	printf("%d",ans==-1?0:ans);
	return 0;
} 
