#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=100000*70+5;
	const int M=1e9;
	
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
			static int bask[20];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	namespace Tree
	{
		int cnt,sum[N],ls[N],rs[N];

		void insert(int &root,int last,int val,int l=1,int r=M)
		{
			root=++cnt;
			sum[root]=sum[last]+val;
			ls[root]=ls[last],rs[root]=rs[last];
			if(l==r) return;
			int mid=(l+r)>>1;
			if(val<=mid) insert(ls[root],ls[last],val,l,mid);
			else insert(rs[root],rs[last],val,mid+1,r);
		}

		int query(int x,int y,int s,int e,int l=1,int r=M)
		{
			if(s<=l&&r<=e) return sum[y]-sum[x];
			int mid=(l+r)>>1,ans=0;
			if(s<=mid) ans+=query(ls[x],ls[y],s,e,l,mid);
			if(e>mid) ans+=query(rs[x],rs[y],s,e,mid+1,r);
			return ans;
		}
	}

	void work()
	{
		int n=read();
		static int root[N];
		for(int i=1;i<=n;i++)
			Tree::insert(root[i],root[i-1],read());
		int m=read();
		while(m--)
		{
			int l=read(),r=read(),ans,t;
			for(ans=1;;ans=t+1)
			{
				t=Tree::query(root[l-1],root[r],1,ans);
				if(t<ans) break;
			}
			write(ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
