#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<iostream>
using namespace std;

namespace Tree
{
	const int N=400010;
	int sum[N],tag[N];
	
	inline void update(int root)
	{
		sum[root]=sum[root<<1]+sum[root<<1|1];
	}

	inline void pushdown(int root,int l,int r)
	{
		if(!tag[root]) return;
		int mid=(l+r)>>1,val=tag[root];
		sum[root<<1]=(mid-l+1)*val;
		sum[root<<1|1]=(r-mid)*val;
		tag[root<<1]=tag[root<<1|1]=val;
		tag[root]=0;
	}

	void build(int root,int l,int r)
	{
		tag[root]=0;
		if(l==r) {sum[root]=1;return;}
		int mid=(l+r)>>1;
		build(root<<1,l,mid);
		build(root<<1|1,mid+1,r);
		update(root);
	}

	void cover(int root,int l,int r,int s,int e,int val)
	{
		if(s>r||e<l) return;
		if(s<=l&&r<=e) 
		{
			sum[root]=(r-l+1)*val;
			tag[root]=val;
			return;
		}
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		cover(root<<1,l,mid,s,e,val);
		cover(root<<1|1,mid+1,r,s,e,val);
		update(root);
	}
}

namespace TYC
{
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		int T=read();
		for(int kase=1;kase<=T;kase++)
		{
			int n=read(),m=read();
			Tree::build(1,1,n);
			while(m--)
			{
				int l=read(),r=read(),x=read();
				Tree::cover(1,1,n,l,r,x);
			}
			printf("Case %d: The total value of the hook is %d.",kase,Tree::sum[1]);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
