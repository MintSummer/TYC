#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef long double ld;
	typedef pair<int,int> pa;

	const int N=400010;

	int n,start[N],end[N];
	multiset<int> s;
	typedef multiset<int>::iterator iter;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	bool cmp(const int &x,const int &y) 
	{
		return start[x]<start[y];
	}

	void work()
	{
		int T=read();
		while(T--)
		{
			int n=read();
			memset(start,0,sizeof(start));
			memset(end,0,sizeof(end));
			static int list[N];
			for(int i=1;i<=n;i++)
				start[i]=read(),end[i]=read(),list[i]=i;
			sort(list+1,list+1+n,cmp);
			s.clear();
			ll ans=0;
			for(int i=1;i<=n;i++)
			{
				int x=list[i];
				iter it=s.upper_bound(start[x]);
				if(it==s.begin())
					ans+=end[x]-start[x];
				else
				{
					it--;
					ans+=end[x]-*it;
					s.erase(it);
				}
				s.insert(end[x]);
			}
			printf("%d %lld\n",(int)s.size(),ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
