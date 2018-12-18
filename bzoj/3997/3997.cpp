#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1010;
	int T,n,m,a[N][N];
	ll f[N][N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		T=read();
		while(T--)
		{
			n=read(),m=read();
			for(int i=1;i<=n;i++) 
				for(int j=1;j<=n;j++) 
					a[i][j]=read();
			for(int i=1;i<=n;i++)
				for(int j=m;j;j--)
					f[i][j]=max(f[i-1][j+1]+a[i][j],max(f[i-1][j],f[i][j+1]));
			printf("%lld\n",f[n][1]);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
