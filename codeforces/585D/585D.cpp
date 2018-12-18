#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	typedef long long ll;
	const int N=30;	
	const int inf=0x3f3f3f3f;

	int n,Mid,a[N],b[N],c[N];
	ll sum=-inf,ans,Pow;
	map<pa,pa> mp;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void dfs1(int now,ll A,ll B,ll C,ll state)
	{
		if(now>Mid)
		{
			pa tmp=pa(A-B,B-C);
			if(mp.count(tmp))
			{
				if(A>mp[tmp].first)
					mp[tmp]=pa(A,state);
			}
			else mp[tmp]=pa(A,state);
			return;
		}
		dfs1(now+1,A+a[now],B+b[now],C,state*3+0);
		dfs1(now+1,A+a[now],B,C+c[now],state*3+1);
		dfs1(now+1,A,B+b[now],C+c[now],state*3+2);
	}

	void dfs2(int now,ll A,ll B,ll C,ll state)
	{
		if(now>n)
		{
			pa tmp=pa(B-A,C-B);
			if(mp.count(tmp))
			{
				pa x=mp[tmp];
				if(A+x.first>sum)
					sum=A+x.first,ans=x.second*Pow+state;
			}
			return;
		}
		dfs2(now+1,A+a[now],B+b[now],C,state*3+0);
		dfs2(now+1,A+a[now],B,C+c[now],state*3+1);
		dfs2(now+1,A,B+b[now],C+c[now],state*3+2);
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),b[i]=read(),c[i]=read();
		Mid=n>>1;
		Pow=pow(3,n-Mid);
		dfs1(1,0,0,0,0);
		dfs2(Mid+1,0,0,0,0);
		if(sum==-inf) puts("Impossible");
		else 
		{
			static int len,bask[50];
			while(ans) bask[++len]=ans%3,ans/=3;
			for(int i=len+1;i<=n;i++) puts("LM");
			for(;len;len--)
			{
				switch(bask[len])
				{
					case 0: puts("LM");break;
					case 1: puts("LW");break;
					case 2: puts("MW");break;
				}
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
