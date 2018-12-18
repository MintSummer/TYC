//定义dp[i][j]表示第i趟的时候到第j楼层的方案数。 
//转移方程dp[i][j] += dp[i-1][k] (k = 1,….,n) 
//对当前的O(n^3)进行优化，可以发现从一个位置能到的位置为一段区间
//考虑前缀和和差分，若j能到的区间为l~r，就给dp[i+1][l]+dp[i][j],dp[i+1][r+1]-dp[i][j]
//计算前缀和即可 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
	const int p=1e9+7,N=5010;
	int dp[N][N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	void add(int now,int l,int r,int val)
	{
		dp[now][l]=(dp[now][l]+val)%p;
		dp[now][r]=(dp[now][r]-val+p)%p;//减法注意不要减成负数 
	}
	
	void work()
	{
		int n=read(),a=read(),b=read(),k=read();
		dp[0][a]=1;//起点 
		for(int i=0;i<k;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(j==b) continue;
				int tmp=abs(j-b)-1;
				int l=max(j-tmp,1),r=min(j+tmp,n);
				add(i+1,l,j,dp[i][j]);
				add(i+1,j+1,r+1,dp[i][j]);//j不能到j 
				//将当前的值给此时暂且不用的i+1，不影响第i层的答案，然后会重新覆盖第i+1层 
			}
			int sum=0;
			for(int j=1;j<=n;j++)
			{
				sum=(sum+dp[i+1][j])%p;
				dp[i+1][j]=sum;//更新成前缀和的实际值 
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=(ans+dp[k][i])%p;
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
