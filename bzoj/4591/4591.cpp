#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	const int p=2333,N=2350;
	typedef long long ll;
	int C[N][N],f[N][N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline int Mod(int x) {return x>=p?x-p:x;}

	inline void init()
	{
		C[0][0]=1;
		for(int i=1;i<p;i++)
		{
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=Mod(C[i-1][j-1]+C[i-1][j]);
		}
		for(int i=0;i<p;i++)
			for(int j=0;j<p;j++)
				f[i][j]=Mod(f[i][j-1]+C[i][j]);
	}

	inline int Lucas(ll n,ll m)
	{
		if(!m) return 1;
		if(n<m) return 0;
		return C[n%p][m%p]*Lucas(n/p,m/p)%p;
	}

	inline int F(ll n,ll k)
	{
		if(!k||!k) return 1;
		if(n<p&&k<p) return f[n][k];
		return Mod(f[n%p][p-1]*F(n/p,k/p-1)%p+Lucas(n/p,k/p)*f[n%p][k%p]%p);
	}

	void work()
	{
		init();
		int T=read();
		while(T--)
		{
			ll n=read(),k=read();
			printf("%d\n",F(n,k));
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
