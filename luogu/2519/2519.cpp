#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

namespace Tree
{
	const int N=400010,inf=0x3f3f3f3f;
	int mx[N];

	void insert(int root,int l,int r,int x,int val)
	{
		if(l==r) {mx[root]=max(mx[root],val);return;}
		int mid=(l+r)>>1;
		if(x<=mid) insert(root<<1,l,mid,x,val);
		else insert(root<<1|1,mid+1,r,x,val);
		mx[root]=max(mx[root<<1],mx[root<<1|1]);
	}

	int query(int root,int l,int r,int s,int e)
	{
		if(e<l||s>r) return 0;
		if(s<=l&&r<=e) return mx[root];
		int mid=(l+r)>>1;
		return max(query(root<<1,l,mid,s,e),query(root<<1|1,mid+1,r,s,e));
	}
}

namespace TYC
{
	const int N=100010;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct Interval
	{
		int l,r,val;
		bool operator < (const Interval &a) const 
		{
			return (r<a.r)||(r==a.r&&l<a.l);
		}
	}x[N],tmp;
	map<Interval,int> id;

	void work()
	{
		int n=read(),tot=0;
		for(int i=1;i<=n;i++)
		{
			int a=read(),b=read();
			if(a+b>=n) continue;
			tmp=(Interval){a+1,n-b,1};
			if(id.count(tmp)) x[id[tmp]].val++;
			else id[tmp]=++tot,x[tot]=tmp;
		}
		sort(x+1,x+1+tot);
		for(int i=1;i<=tot;i++)
		{
			int mx=Tree::query(1,1,n,1,x[i].l-1);
			int dp=mx+min(x[i].val,x[i].r-x[i].l+1);	
			Tree::insert(1,1,n,x[i].r,dp);
		}
		printf("%d\n",n-Tree::mx[1]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
