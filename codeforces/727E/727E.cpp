#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,ll> pll;
	const int MAXN=1e6+10,seed=131,p[2]={(int)1e9+7,(int)1e9+9};
	int n,k,g,vis[MAXN],ans[MAXN];
	ll F[MAXN*2][2],h[MAXN*2][2];
	map<pll,int> id;
	string str;
	
	inline void init(const string &str)
	{
		F[0][0]=F[0][1]=1;
		for(int i=1;i<str.size();i++)
		{
			F[i][0]=F[i-1][0]*seed%p[0];
			F[i][1]=F[i-1][1]*seed%p[1];
		}
		h[0][0]=h[0][1]=str[0]-'a';
		for(int t=0;t<2;t++)
			for(int i=1;i<str.size();i++)
				h[i][t]=(h[i-1][t]*seed+str[i]-'a')%p[t];
	}
	
	inline pll get_hash(const string &s)
	{
		ll ans[2]={0,0};
		for(int t=0;t<2;t++)
			for(int i=0;i<s.size();i++)
				ans[t]=(ans[t]*seed+s[i]-'a')%p[t];
		return make_pair(ans[0],ans[1]);
	}
	
	inline pll Hash(int lt,int rt)
	{
		int len=rt-lt+1;
		if(lt==0) return make_pair(h[rt][0],h[rt][1]);
		return make_pair(
			(h[rt][0]-h[lt-1][0]*F[len][0]%p[0]+p[0])%p[0],
			(h[rt][1]-h[lt-1][1]*F[len][1]%p[1]+p[1])%p[1]);
	}
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin>>n>>k>>str;
		int len=n*k;
		str+=str.substr(0,k);
		init(str);
		cin>>g;
		for(int i=1;i<=g;i++)
		{
			cin>>str;
			id[get_hash(str)]=i;
		}
		bool flag=false;
		memset(vis,-1,sizeof(vis));
		for(int i=0;i<k&&!flag;i++)
		{
			pll pa;
			int cnt=0;
			for(int j=i;j<len+i&&cnt<n;j+=k)
				if(id.count(pa=Hash(j,j+k-1)) && vis[id[pa]]!=i)
					ans[++cnt]=id[pa],vis[id[pa]]=i;
				else break;
			if(cnt==n) flag=true;
		}
		if(flag) 
		{
			puts("YES");
			for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		}
		else puts("NO");
	}
}

int main()
{
	TYC::work();
	return 0;
}
