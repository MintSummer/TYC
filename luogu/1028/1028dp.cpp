#include<bits/stdc++.h>
using namespace std;
int n,dp[1010];

int main() 
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) dp[i]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i/2;j++)
			dp[i]+=dp[j];
	printf("%d",dp[n]);
}
