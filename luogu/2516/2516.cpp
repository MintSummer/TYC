#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=5010;
	const int p=100000000;

	char A[N],B[N];
	int dp[2][N],num[2][N];

	inline void Mod(int &x) {x=(x>=p?x-p:x);}

	void work()
	{
		scanf("%s%s",A+1,B+1);
		int la=strlen(A+1)-1,lb=strlen(B+1)-1;
		for(int i=0;i<=lb;i++) num[0][i]=1;
		num[1][0]=1;
		for(int i=1,now=1;i<=la;i++,now^=1)
		{
			for(int j=1;j<=lb;j++)
			{
				num[now][j]=0;
				dp[now][j]=max(dp[now][j-1],dp[now^1][j]);
				if(A[i]==B[j]) dp[now][j]=max(dp[now][j],dp[now^1][j-1]+1);
				if(dp[now][j]==dp[now][j-1]) 
					Mod(num[now][j]+=num[now][j-1]);
				if(dp[now][j]==dp[now^1][j]) 
					Mod(num[now][j]+=num[now^1][j]);
				if(A[i]==B[j]&&dp[now][j]==dp[now^1][j-1]+1)
					Mod(num[now][j]+=num[now^1][j-1]);
				if(A[i]!=B[j]&&dp[now^1][j-1]==dp[now][j])
					Mod(num[now][j]+=-num[now^1][j-1]+p);
			}
		}
		printf("%d\n%d\n",dp[la&1][lb],num[la&1][lb]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
