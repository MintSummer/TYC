#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,int> pli;
	const int N=1e6+10;

	int n,k,num,arr[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(ll x)
	{
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
	}

	inline bool cmp(const int &x,const int &y)
	{
		return (arr[x]<arr[y])||(arr[x]==arr[y]&&x<y);
	}

	ll subtask1()
	{
		static int list[N];
		static ll ans[N];
		static priority_queue<pli,vector<pli>,greater<pli> > q;
		for(int i=1;i<=n;i++) list[i]=i;
		sort(list+1,list+1+n,cmp);
		q.push(make_pair(arr[list[1]],1));
		for(int i=1;i<=k;i++)
		{
			pli now=q.top();q.pop();
			int pos=now.second;
			ans[i]=now.first;
			if(pos!=n) 	 	 
			{
				q.push(make_pair(now.first-arr[list[pos]]+arr[list[pos+1]],pos+1));
				q.push(make_pair(now.first+arr[list[pos+1]],pos+1));
			}	
		}
		write(ans[k]),putchar('\n');
		for(int i=k;i&&ans[i]==ans[k];i--) num++;
		return ans[k];
	}

	namespace Tree
	{
		int mn[N<<2];

		#define ls root<<1
		#define rs root<<1|1

		inline bool cmp(const int &x,const int &y)
		{
			return y==-1?x>y:(arr[x]==arr[y]?(x<y):(arr[x]<arr[y]));
		}

		void build(const int root,const int l,const int r)
		{
			if(l==r) {mn[root]=l;return;}
			int mid=(l+r)>>1;
			build(ls,l,mid),build(rs,mid+1,r);
			mn[root]=min(mn[ls],mn[rs],cmp);
		}

		int query(const int root,int l,const int r,const int s,const int e,const ll val)
		{
			if(l==r) return arr[l]<=val?l:-1;
			int mid=(l+r)>>1,t;
			if(s<=l&&r<=e)
			{
				if(arr[mn[root]]>val) return -1;
				if(arr[mn[ls]]<=val) return query(ls,l,mid,s,e,val);
				else return query(rs,mid+1,r,s,e,val);
			}
			if(s<=mid) if(~(t=query(ls,l,mid,s,e,val))) return t;
			if(e>mid) return query(rs,mid+1,r,s,e,val);
			else return t;
		}
	}

	void dfs(int from,ll res)
	{
		static int top,sta[N];
		if(!num) return;	
		if(!res)
		{
			if(!(--num)) 
				for(int i=1;i<=top;i++) write(sta[i]),putchar(' ');
			return;
		}
		for(int i=from,t;i<=n;i=t+1)
		{
			t=Tree::query(1,1,n,i,n,res);
			if(t==-1) break;
			else
			{
				sta[++top]=t;	
				dfs(t+1,res-arr[t]);
				top--;
			}
		}
	}	

	void work()
	{
		n=read(),k=read()-1;
		if(k==-1) {puts("0");return;}
		for(int i=1;i<=n;i++) arr[i]=read(); 
		Tree::build(1,1,n);
		dfs(1,subtask1());
	}
}

int main()
{
	TYC::work();
	return 0;
}
