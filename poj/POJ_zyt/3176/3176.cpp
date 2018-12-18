#include<iostream>
#include<algorithm>
using namespace std;
int dp[360][360],map[360][360],n;
int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			cin>>map[i][j];
	for(int i=0;i<n;i++)
		dp[n-1][i]=map[n-1][i];
	for(int i=n-2;i>=0;i--)
		for(int j=0;j<=i;j++)
			dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+map[i][j];
	cout<<dp[0][0];
}
