#include<iostream>
#include<algorithm>
using namespace std;
int n,m,dp[12890],w[3412],d[3412];
int main(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i]>>d[i];
	for(int i=1;i<=n;i++)
		for(int j=m;j>=w[i];j--)
			dp[j]=max(dp[j],dp[j-w[i]]+d[i]);
	cout<<dp[m];
	return 0;
}
 
