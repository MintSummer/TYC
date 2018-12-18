#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1<<20|5;
	const int p=1e9+7;

	int arr[N],dp[10][N],f[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline int Mod(const int x,const int y) 
	{
		int t=x+y;
		return t>=p?t-p:t;
	}

	void work()
	{
		int n=read(),d=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		sort(arr+1,arr+1+n);
		dp[0][0]=1;
		for(int i=1,lim=1;i<=n;i++)
		{
			while(lim<=arr[i]) lim<<=1;
			for(int j=0;j<=lim;j++)
				f[j]=Mod(dp[d-1][j],dp[0][j^arr[i]]);
			for(int res=d-1;res;res--)
				for(int j=0;j<=lim;j++)
					if(j<=(j^arr[i]))
					{
						int t=dp[res][j];
						dp[res][j]=Mod(dp[res-1][j],dp[res][j^arr[i]]);
						dp[res][j^arr[i]]=Mod(dp[res-1][j^arr[i]],t);
					}
			for(int j=0;j<=lim;j++)
				dp[0][j]=f[j];
		}
		printf("%d\n",Mod(dp[0][0],-(n%d==0)+p));
	}
}

int main()
{
	TYC::work();
	return 0;
}
