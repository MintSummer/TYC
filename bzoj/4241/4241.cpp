#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10,B=320;

	int n,m,block,arr[N],real[N],belong[N],end[B],f[B][N];
	vector<int> pos[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
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

	inline int times(const int num,const int l,const int r)
	{
		return upper_bound(pos[num].begin(),pos[num].end(),r)-
			   lower_bound(pos[num].begin(),pos[num].end(),l);
	}

	void init()
	{
		block=sqrt(n);
		for(int i=1;i<=n;i++) 
			belong[i]=(i-1)/block+1;
		int tot=belong[n];
		for(int i=1;i<=tot;i++)
			end[i]=end[i-1]+block;
		for(int i=1;i<=tot;i++)
		{
			int start=end[i-1]+1,p=0;
			ll mx=0;
			for(int j=start;j<=n;j++)
			{
				ll t=(ll)real[arr[j]]*times(arr[j],start,j);
				if(t>mx) mx=t,p=arr[j];
				f[i][j]=p;
			}
		}
	}

	inline ll query(const int l,const int r)
	{
		int bl=belong[l],br=belong[r];
		ll ans=0;
		if(bl==br)
			for(int i=l;i<=r;i++)
				ans=max(ans,(ll)real[arr[i]]*times(arr[i],l,r));
		else
		{

			ans=real[f[bl+1][r]]*times(f[bl+1][r],l,r);
			for(int i=l;i<=end[bl];i++)
				ans=max(ans,(ll)real[arr[i]]*times(arr[i],l,r));
		}
		return ans;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) 
			real[i]=arr[i]=read();
		sort(real+1,real+1+n);
		int num=unique(real+1,real+1+n)-real-1;
		for(int i=1;i<=n;i++)
		{
			arr[i]=lower_bound(real+1,real+1+num,arr[i])-real;
			pos[arr[i]].push_back(i);
		}
		init();
		while(m--)
		{
			int l=read(),r=read();
			if(l>r) puts("0");
			else write(query(l,r));
		}
	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
