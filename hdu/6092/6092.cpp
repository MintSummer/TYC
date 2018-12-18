#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef long double ld;
	typedef pair<int,int> pa;

	const int N=1e4+10;

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
	}

	void work()
	{
		int T=read();
		static ll res[N],b[N];
		static int num[N];
		while(T--)
		{
			int n=read(),m=read();
			memset(res,0,sizeof(res));
			memset(num,0,sizeof(num));
			for(int i=0;i<=m;i++) b[i]=read();
			res[0]=1;
			for(int now=1;now<=m;now++)
			{
				num[now]=b[now]-res[now];
				for(int i=1;i<=num[now];i++)
					for(int j=m;j>=now;j--)
						res[j]+=res[j-now];
			}
			int tot=0;
			for(int i=1;i<=m;i++)
				for(int j=1;j<=num[i];j++)
				{
					write(i);
					++tot;
					if(tot!=n) putchar(' ');
				}
			putchar('\n');
		}	
	}
}

int main()
{
	TYC::work();
	return 0;
}

