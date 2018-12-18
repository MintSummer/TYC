#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
const int P=1e9;
long long n,ans,a[50],dp[1000010];

int main()
{
	memset(dp,0,sizeof(dp));
	scanf("%d",&n);
	int sum=1,cnt=0;
	while(sum<=n)
	  {
	  	cnt++;
	  	a[cnt]=sum;
	  	sum=sum*2;
	  }
	dp[0]=0,dp[1]=1,dp[2]=2;
	for(int i=3;i<=n;i++)
	  {
	  	if(i%2==1) dp[i]=dp[i-1];
		else dp[i]=(dp[i-1]+dp[i/2])%P;
	  	/*若i为奇数，则就只能为i-1的所有情况均+1，故总个数应该不变,且不会发生重复或漏写 
	  	若i为偶数:
	  	因为排列组合的数必为升序排列 
	  	若排列的首个数为1，则i的个数就应为i-1的所有情况+1，个数不变，不重复（可能出现连续多个1的情况，首位的1不参与合并）
		若排列的首个数为2，则排列中不可能出现一个1，将集合中所有数/2，得到i/2的所有排列情况
		总共合起来就是dp[i]=dp[i-1]+dp[i/2] */
	  }
	printf("%lld",dp[n]%P);
	return 0;
}