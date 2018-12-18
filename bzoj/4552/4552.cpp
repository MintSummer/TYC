#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;

	int n,m,pos,arr[N];
	struct Opt
	{
		int op,l,r;
	}opt[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	namespace Tree
	{
		struct node
		{
			int tag,num0,num1;
		}tree[N<<2];
		#define ls root<<1
		#define rs root<<1|1
		
		inline void update(node &root,const node &L,const node &R)
		{
			root.num0=L.num0+R.num0;
			root.num1=L.num1+R.num1;
		}

		inline void pushdown(const int root,const int l,const int r)
		{
			int &t=tree[root].tag,mid=(l+r)>>1;
			if(t==-1) return;
			if(!t) 
			{
				tree[ls].num0=mid-l+1;
				tree[rs].num0=r-mid;
				tree[ls].num1=tree[rs].num1=0;
			}
			else
			{
				tree[ls].num1=mid-l+1;
				tree[rs].num1=r-mid;
				tree[ls].num0=tree[rs].num0=0;
			}
			tree[ls].tag=tree[rs].tag=t;
			t=-1;
		}

		void build(const int root,const int l,const int r,const int val)
		{
			tree[root].tag=-1;
			tree[root].num0=tree[root].num1=0;
			if(l==r) 
			{
				if(arr[l]>val) tree[root].num1++;
				else tree[root].num0++;
				return;
			}
			int mid=(l+r)>>1;
			build(ls,l,mid,val);
			build(rs,mid+1,r,val);
			update(tree[root],tree[ls],tree[rs]);
		}

		void cover(const int root,const int l,const int r,const int s,const int e,const int val)
		{
			if(s<=l&&r<=e)
			{
				tree[root].tag=val;
				if(!val) tree[root].num0=r-l+1,tree[root].num1=0;
				else tree[root].num1=r-l+1,tree[root].num0=0;
				return;
			}
			pushdown(root,l,r);
			int mid=(l+r)>>1;
			if(s<=mid) cover(ls,l,mid,s,e,val);
			if(e>mid) cover(rs,mid+1,r,s,e,val);
			update(tree[root],tree[ls],tree[rs]);
		}

		node query(const int root,const int l,const int r,const int s,const int e)
		{
			if(s<=l&&r<=e) return tree[root];
			pushdown(root,l,r);
			int mid=(l+r)>>1;
			if(e<=mid) return query(ls,l,mid,s,e);
			else if(s>mid) return query(rs,mid+1,r,s,e);
			else 
			{
				node ans;
				update(ans,query(ls,l,mid,s,e),query(rs,mid+1,r,s,e));
				return ans;
			}
		}
	}
	using namespace Tree;

	bool check(const int mid)
	{
		build(1,1,n,mid);
		for(int i=1;i<=m;i++)
		{
			int l=opt[i].l,r=opt[i].r;
			node interval=query(1,1,n,l,r);
			int num[2]={interval.num0,interval.num1};
			cover(1,1,n,l,l+num[opt[i].op]-1,opt[i].op);
			cover(1,1,n,l+num[opt[i].op],r,opt[i].op^1);
		}
		return query(1,1,n,pos,pos).num0;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		for(int i=1;i<=m;i++)
			opt[i]=(Opt){read(),read(),read()};
		pos=read();
		int l=1,r=n,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
