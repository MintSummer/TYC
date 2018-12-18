#include<bits/stdc++.h>
using namespace std;

namespace Tree
{
	const int N=1e6+10;
	struct node
	{
		int sum,mn,mx,tagadd,tagcov;
		void push(int l,int r,int a,int c)
		{
			if(!c)
			{
				sum+=a*(r-l+1);
				mx+=a,mn+=a;
				tagadd+=a;
			}
			else
			{
				sum=(a+c)*(r-l+1);
				mx=mn=a+c;
				tagcov=c;
				tagadd=a;
			}
		}
	}tree[N*4];

	inline void update(int root)
	{
		tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
		tree[root].mx=max(tree[root<<1].mx,tree[root<<1|1].mx);
		tree[root].mn=min(tree[root<<1].mn,tree[root<<1|1].mn);
	}

	inline void pushdown(int root,int l,int r)
	{
		int mid=(l+r)>>1;
		tree[root<<1].push(l,mid,tree[root].tagadd,tree[root].tagcov);
		tree[root<<1|1].push(mid+1,r,tree[root].tagadd,tree[root].tagcov);
		tree[root].tagadd=tree[root].tagcov=0;
	}
	
	void add(int root,int l,int r,int s,int e,int val)
	{
		if(s>r||e<l) return;
		if(s<=l&&r<=e) 
		{
			tree[root].sum+=val*(r-l+1);
			tree[root].mx+=val;
			tree[root].mn+=val;
			tree[root].tagadd+=val;
			return;
		}
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		add(root<<1,l,mid,s,e,val);
		add(root<<1|1,mid+1,r,s,e,val);
		update(root);
	}

	void cover(int root,int l,int r,int s,int e,int val)
	{
		if(s>r||e<l) return;
		if(s<=l&&r<=e)
		{
			tree[root].sum=val*(r-l+1);
			tree[root].mx=val;
			tree[root].mn=val;
			tree[root].tagcov=val;
			tree[root].tagadd=0;
			return;
		}
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		cover(root<<1,l,mid,s,e,val);
		cover(root<<1|1,mid+1,r,s,e,val);
		update(root);
	}

	node query(int root,int l,int r,int s,int e)
	{
		if(s<=l&&r<=e) return tree[root];
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		if(e<=mid) return query(root<<1,l,mid,s,e);
		else if(s>mid) return query(root<<1|1,mid+1,r,s,e);
		else 
		{
			node L=query(root<<1,l,mid,s,mid),R=query(root<<1|1,mid+1,r,mid+1,e),ans;
			ans.sum=L.sum+R.sum;
			ans.mx=max(L.mx,R.mx);
			ans.mn=min(L.mn,R.mn);
			return ans;
		}	
	}
}

namespace TYC
{
	using namespace Tree;
	int n,m,q;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		while(~scanf("%d",&n))
		{
			memset(tree,0,sizeof(tree));
			m=read(),q=read();
			int tot=n*m,opt,x1,x2,y1,y2,val,sum,mx,mn;
			while(q--)
			{
				opt=read(),x1=read(),y1=read(),x2=read(),y2=read();
				switch(opt)
				{
					case 1: 
						val=read();
						for(int i=x1;i<=x2;i++)
						{
							int l=(i-1)*m+y1,r=(i-1)*m+y2;
							add(1,1,tot,l,r,val);
						}
						break;
					case 2:
						val=read();
						for(int i=x1;i<=x2;i++)
						{
							int l=(i-1)*m+y1,r=(i-1)*m+y2;
							cover(1,1,tot,l,r,val);
						}
						break;
					case 3:
						sum=0,mx=0,mn=0x3f3f3f3f;
						for(int i=x1;i<=x2;i++)
						{
							int l=(i-1)*m+y1,r=(i-1)*m+y2;
							node tmp=query(1,1,tot,l,r);
							sum+=tmp.sum;
							mx=max(mx,tmp.mx);
							mn=min(mn,tmp.mn);
						}
						printf("%d %d %d\n",sum,mn,mx);
						break;
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
