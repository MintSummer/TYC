#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int p=99999997;
	const int N=100010;
	#define lowbit(x) x&(-x)
	#define Mod(x) x>p?x-p:x
	int n,a[N],b[N],to[N],c[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct node
	{
		int id,x;
		bool operator < (const node &t) const
		{
			return (x<t.x)||(x==t.x&&id<t.id);
		}
	}tmpa[N],tmpb[N];

	inline void add(int x,int val)
	{
		for(;x<=n;x+=lowbit(x)) c[x]+=val;
	}
	
	inline int query(int x)
	{
		int ans=0;
		for(;x;x-=lowbit(x)) ans=Mod(ans+c[x]);
		return ans;
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++) 
			tmpa[i]=(node){i,read()};
		for(int i=1;i<=n;i++) 
			tmpb[i]=(node){i,read()};
		int tot=0;
		sort(tmpa+1,tmpa+1+n);
		sort(tmpb+1,tmpb+1+n);
		for(int i=1;i<=n;i++)
			b[tmpb[i].id]=tmpa[++tot].id;
		long long ans=0;
		for(int i=n;i;i--)
		{
			ans=Mod(ans+query(b[i]));
			add(b[i],1);
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
