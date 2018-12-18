#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
const int p=19650827;
int n,a[MAXN],dp[MAXN][MAXN][2];
//对于最终序列的一个区间[l,r]，最后一个添加的只可能是第l个人或者第r个人。 
//dp[i][j][0/1]表示取到数列中从i到j的区间，上一个取到的是数列左边/右边的数

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) dp[i][i][0]=1;
	for(int len=2;len<=n;len++)//枚举区间长度 
		for(int i=1;i<=n-len+1;i++)//枚举左端点位置 
		{
			int j=i+len-1;//右端点 
			if(a[i]<a[i+1]) dp[i][j][0]+=dp[i+1][j][0];
			if(a[i]<a[j]) dp[i][j][0]+=dp[i+1][j][1];
			if(a[j]>a[j-1]) dp[i][j][1]+=dp[i][j-1][1];
			if(a[j]>a[i]) dp[i][j][1]+=dp[i][j-1][0];
			dp[i][j][0]%=p,dp[i][j][1]%=p;	
		}
	printf("%d",(dp[1][n][0]+dp[1][n][1])%p);
	return 0;
}
