#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
ll s1[N],s2[N];

namespace Tree
{
	struct node
	{
		ll sum0,sum1,sum2,tag0,tag1,tag2;
		void down(int l,int r,int t0,int t1,int t2)
		{
			sum2+=t2*(s2[r]-s2[l-1]);
			sum1+=t1*(s1[r]-s1[l-1]);
			sum0+=t0*(r-l+1);
			tag0+=t0,tag1+=t1,tag2+=t2;
		}
	}tree[N<<2];

	inline void update(int root,int l,int r)
	{
		tree[root].sum2=tree[root<<1].sum2+tree[root<<1|1].sum2;
		tree[root].sum1=tree[root<<1].sum1+tree[root<<1|1].sum1;
		tree[root].sum0=tree[root<<1].sum0+tree[root<<1|1].sum0;
	}

	inline void pushdown(int root,int l,int r)
	{
		int mid=(l+r)>>1,t0=tree[root].tag0,t1=tree[root].tag1,t2=tree[root].tag2;
		tree[root<<1].down(l,mid,t0,t1,t2);
		tree[root<<1|1].down(mid+1,r,t0,t1,t2);
		tree[root].tag0=0,tree[root].tag1=0,tree[root].tag2=0;
	}

	void change(int root,int l,int r,int s,int e,int val)
	{
		if(s>r||e<l) return;
		if(s<=l&&r<=e) 
		{
			tree[root].sum2+=val*(s2[r]-s2[l-1]);
			tree[root].sum1+=val*(s1[r]-s1[l-1]);
			tree[root].sum0+=val*(r-l+1);
			tree[root].tag2+=val;
			tree[root].tag1+=val;
			tree[root].tag0+=val;
			return;
		}
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		change(root<<1,l,mid,s,e,val),change(root<<1|1,mid+1,r,s,e,val);
		update(root,l,r);
	}

	node query(int root,int l,int r,int s,int e)
	{
		if(s>r||e<l) return (node){0LL,0LL,0LL};
		if(s<=l&&r<=e) return tree[root];
		pushdown(root,l,r);
		int mid=(l+r)>>1;
		node pl=query(root<<1,l,mid,s,e),pr=query(root<<1|1,mid+1,r,s,e),ans;
		ans.sum0=pl.sum0+pr.sum0;
		ans.sum1=pl.sum1+pr.sum1;
		ans.sum2=pl.sum2+pr.sum2;
		return ans;
	}
}

namespace TYC
{
	int n,m;
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	ll gcd(ll a,ll b)
	{
		return !b?a:gcd(b,a%b);
	}

	void work()
	{
		n=read(),m=read();
		n--;
		for(int i=1;i<=n;i++) 
			s1[i]=s1[i-1]+i,s2[i]=s2[i-1]+(ll)i*i;
		char ch;int l,r;
		while(m--)
		{
			do{ch=getchar();} while(ch!='C'&&ch!='Q');
			l=read(),r=read();
			r--;
			if(ch=='C') Tree::change(1,1,n,l,r,read());
			else 
			{
				Tree::node ans=Tree::query(1,1,n,l,r);
				ll up=-ans.sum2+(l+r)*ans.sum1+(-(ll)l*r-l+r+1)*ans.sum0,down=(ll)(r-l+1)*(r-l+2)/2;
				ll g=gcd(up,down);
				up/=g,down/=g;
				printf("%lld/%lld\n",up,down);
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
