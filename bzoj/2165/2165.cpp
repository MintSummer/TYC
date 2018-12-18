#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=110;
	const ll inf=1e18;
	int n;
	ll len;
	
	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct Matrix
	{
		ll m[N][N];
		
		void copy(const Matrix &a)
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					m[i][j]=a.m[i][j];
		}
		
		Matrix operator *(const Matrix &a) 
		{
			Matrix ans;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
				{
					ans.m[i][j]=-inf;
					for(int k=1;k<=n;k++)
						ans.m[i][j]=max(ans.m[i][j],m[i][k]+a.m[k][j]);
					if(ans.m[i][j]>len) ans.m[i][j]=len;
				}
			return ans;
		}
	}M[100];
	
	bool check(Matrix &T)
	{
		for(int i=1;i<=n;i++)
			if(T.m[1][i]>=len) return true;
		return false;
	}
	
	void work()
	{
		int T=read();
		while(T--)
		{
			n=read(),len=read();
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
				{
				 	M[0].m[i][j]=read();
				 	if(!M[0].m[i][j]) M[0].m[i][j]=-inf;
				}
			int i;
			for(i=1;;i++)
			{
				M[i]=M[i-1]*M[i-1];
				if(check(M[i])) break;
			}
			ll ans=1;
			Matrix now=M[0];
			for(i--;i>=0;i--)
			{
				Matrix tmp=M[i]*now;
				if(!check(tmp))
					now.copy(tmp),ans+=(1LL<<i);
			}
			printf("%lld\n",ans+1);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
