#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[30010],ans=0x3f3f3f3f,dp[30010];

int main()
{
	int num1,num2;
	num1=0,num2=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	  {
	  	scanf("%d",&a[i]);
	  	a[i]==1?num1++:num2++;
	  }
	  
	dp[0]=num1,dp[n]=num2;
	ans=min(dp[0],dp[n]);
	
	for(int i=1;i<=n;i++)
	  {
	  	if(a[i]==1) dp[i]=dp[i-1]-1;
	  	else dp[i]=dp[i-1]+1;
	  	ans=min(ans,dp[i]);
	  }
	printf("%d",ans);
	return 0;
}