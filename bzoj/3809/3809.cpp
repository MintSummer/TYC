#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=100010,MX=100000,B=320,M=1e6+10;
	int n,m,block,a[N],ans[M],num[N],belong[N],be[N],sum[B],end[B];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(int x)
	{
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}
	
	struct ques
	{
		int l,r,a,b,id;
		bool operator < (const ques &t) const
		{
			return belong[l]==belong[t.l]?r<t.r:belong[l]<belong[t.l];
		}
	}q[M];
	
	inline void add(int x)
	{
		if(!num[x]) sum[be[x]]++;
		num[x]++;
	}
	
	inline void del(int x)
	{
		num[x]--;
		if(!num[x]) sum[be[x]]--;
	}
	
	inline int query(int l,int r)
	{
		int ans=0;
		if(be[l]==be[r]) 
		{
			for(int i=l;i<=r;i++) ans+=(num[i]!=0);
			return ans;
		}
		for(int i=be[l]+1;i<be[r];i++) ans+=sum[i];
		for(int i=l;i<=end[be[l]];i++) ans+=(num[i]!=0);
		for(int i=end[be[r]-1]+1;i<=r;i++) ans+=(num[i]!=0);
		return ans;
	}
	
	void work()
	{
		n=read(),m=read();
		block=sqrt(n);
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;
		for(int i=1;i<=m;i++)
			q[i]=(ques){read(),read(),read(),read(),i};
		sort(q+1,q+1+m);
		for(int i=1;i<=MX;i++) be[i]=(i-1)/B+1;
		for(int i=1;i<=be[MX];i++) end[i]=end[i-1]+B;
		int l=1,r=0;
		for(int i=1;i<=m;i++) 
		{
			while(l<q[i].l) del(a[l++]);
			while(l>q[i].l) add(a[--l]);
			while(r<q[i].r) add(a[++r]);
			while(r>q[i].r) del(a[r--]);
			ans[q[i].id]=query(q[i].a,q[i].b);
		}
		for(int i=1;i<=m;i++) write(ans[i]);
	}
}
 
int main()
{
	TYC::work();
	return 0;
} 
