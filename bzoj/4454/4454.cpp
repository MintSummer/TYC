#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=2010;
	const ll p=1LL<<32;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(ll &x)
	{
		if(!x) putchar('0');
		else
		{
			int len=0;
			static char bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	inline ll Mod(const ll &x,const ll &y)
	{
		ll t=x+y;
		return t>=p?t-p:t;
	}	

	inline int gcd(const int a,const int b)
	{
		return !b?a:gcd(b,a%b);
	}

	void work()
	{
		int T=read();
		static int a[N],b[N];
		while(T--)
		{
			int n=read(),m=read();
			ll ans=0;
			for(int i=1;i<=n;i++) a[i]=read();
			for(int i=1;i<=m;i++) b[i]=read();
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					ans=Mod(ans,gcd(a[i],b[j])^i^j);
			write(ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
