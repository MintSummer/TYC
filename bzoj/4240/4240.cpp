#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=3e5+10;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct node
	{
		int val,id;
		bool operator < (const node &t) const
		{
			return val>t.val;
		}
	}arr[N];

	int n,c[N];
	#define lowbit(x) (x)&(-(x))

	inline void add(const int x)
	{
		for(int i=x;i<=n;i+=lowbit(i)) c[i]++;
	}

	inline int query(const int x)
	{
		int ans=0;
		for(int i=x;i;i-=lowbit(i)) ans+=c[i];
		return ans;
	}
	
	void work()
	{
		n=read();
		for(int i=1;i<=n;i++) 
			arr[i]=(node){read(),i};
		sort(arr+1,arr+1+n);
		ll ans=0;
		for(int i=1,j=1;i<=n;i++)
		{
			if(arr[i].val!=arr[i-1].val) 
				while(j<i) add(arr[j++].id); 
			int t=query(arr[i].id);
			ans+=min(t,j-1-t);
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	freopen("4240.in","r",stdin);
	freopen("4240.out","w",stdout);
	TYC::work();
	return 0;
}
