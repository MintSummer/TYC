#include<iostream>
#include<algorithm> 
using namespace std;
int dp[20000010],n,b,c[21],sum;
int main(void)
{
	cin>>n>>b;
	for(int i=1;i<=n;i++)cin>>c[i],sum+=c[i];
	for(int i=c[1];i<=sum;i++)dp[i]=c[1];
	for(int i=2;i<=n;i++)
		for(int j=sum;j>=c[i];j--)
			dp[j]=max(dp[j],dp[j-c[i]]+c[i]);
	for(int i=1;i<=sum;i++)
		if(dp[i]>=b)
		{
			cout<<dp[i]-b;
			return 0;
		}
}
