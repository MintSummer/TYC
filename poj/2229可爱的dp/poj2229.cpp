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
	  	/*��iΪ���������ֻ��Ϊi-1�����������+1�����ܸ���Ӧ�ò���,�Ҳ��ᷢ���ظ���©д 
	  	��iΪż��:
	  	��Ϊ������ϵ�����Ϊ�������� 
	  	�����е��׸���Ϊ1����i�ĸ�����ӦΪi-1���������+1���������䣬���ظ������ܳ����������1���������λ��1������ϲ���
		�����е��׸���Ϊ2���������в����ܳ���һ��1����������������/2���õ�i/2�������������
		�ܹ�����������dp[i]=dp[i-1]+dp[i/2] */
	  }
	printf("%lld",dp[n]%P);
	return 0;
}