#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=5e5+10;

	int bin[50],num[50][2];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	namespace Trie
	{
		const int M=N*32;                                 
		int cnt,son[M][2],size[M];
		ll sum[M];

		inline void init()
		{
			memset(num,0,sizeof(num));
			for(int i=0;i<=cnt;i++) son[i][0]=son[i][1]=0;
			memset(sum,0,sizeof(ll[cnt+5]));
			memset(size,0,sizeof(int[cnt+5]));
			cnt=0;
		}

		inline ll query(int x)
		{
			int now=0;
			ll ans=0;
			for(int i=30;i;i--)
			{
				int t=int((x&bin[i])!=0),ano=son[now][t^1];
				if(ano)
					ans+=(ll)num[i][t^1]*size[ano]-sum[ano];
				if(!son[now][t]) son[now][t]=++cnt;
				now=son[now][t];
				sum[now]+=num[i][t];
				size[now]++;
			}
			return ans;
		}
	}

	void work()
	{
		int T=read();
		bin[1]=1;
		for(int i=2;i<=30;i++) bin[i]=bin[i-1]<<1;
		while(T--)
		{
			Trie::init();
			int n=read();
			ll ans=0;
			for(int i=1;i<=n;i++)
			{
				int x=read();
				for(int j=1;j<=30;j++)
					num[j][int((x&bin[j])!=0)]++;
				ans+=Trie::query(x);
			}
			printf("%lld\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
